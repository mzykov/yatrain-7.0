#include <iostream>
#include <numeric>
#include <vector>

class UnionFind {
public:
    UnionFind(int n) : n_(n), numSubsets_(n_), v_(std::vector<int>(n_, 0)), counts_(std::vector<int>(n_, 1)) {
        std::iota(v_.begin(), v_.end(), 0);
    }

    int unionElements(int x, int y) {
        int x_label = findLabel(x);
        int y_label = findLabel(y);

        if (x_label == y_label) {
            return x_label;
        } else {
            int result_label = 0;

	    if (counts_[x_label] < counts_[y_label]) {
                replaceLabel(x_label, y_label);
                counts_[y_label] += counts_[x_label];
                counts_[x_label] = 0;
	        result_label = y_label;
	    } else {
	        replaceLabel(y_label, x_label);
                counts_[x_label] += counts_[y_label];
                counts_[y_label] = 0;
	        result_label = x_label;
	    }

            --numSubsets_;

            return result_label;
        }
    }

    const int numSubsets() const {
        return numSubsets_;
    }

    void print() {
        for (const int n : v_)
            std::cout << n << " ";
        std::cout << "\n";
    }
private:
    int n_, numSubsets_;
    std::vector<int> v_, counts_;

    int findLabel(int x) {
        while (x != v_[x])
            x = v_[x];
        return x;
    }

    void replaceLabel(int x, int label) {
        while (x != v_[x]) {
            x = v_[x];
            v_[x] = label;
        }
        v_[x] = label;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    int res = 0;
    UnionFind islands(n);

    while (m--) {
        int x, y;
        std::cin >> x >> y;

        ++res;
        islands.unionElements(--x, --y);
//islands.print();

        if (islands.numSubsets() == 1)
            break;
    }

    std::cout << res << "\n";

    return 0;
}
