#include <array>
#include <iostream>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>

class UnionFind {
public:
    UnionFind(int n) : n_(n), v_(std::vector<int>(n_, 0)), counts_(std::vector<int>(n_, 1)) {
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

            return result_label;
        }
    }

    int findLabel(int x) {
        while (x != v_[x])
            x = v_[x];
        return x;
    }

private:
    int n_;
    std::vector<int> v_, counts_;

    void replaceLabel(int x, int label) {
        while (x != v_[x]) {
            x = v_[x];
            v_[x] = label;
        }
        v_[x] = label;
    }
};

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    int result_length = k - m;
    std::vector<bool> result(result_length, false);

    UnionFind g(n);

    while (m--) {
        int u, v;
        std::cin >> u >> v;
    }

    std::vector<std::array<int,3>> cmd(k, {{0, 0, 0}});

    for (int i = 0; i < k; ++i) {
        std::string cmd_str;
        int u, v;
        std::cin >> cmd_str >> u >> v;

        if (cmd_str == "ask")
            cmd[i][0] = 1;

        cmd[i][1] = --u;
        cmd[i][2] = --v;
    }

    for (int i = k - 1; i >= 0; --i) {
        const auto &c = cmd[i];

        if (c[0] == 1) { // ask
            --result_length;
            if (g.findLabel(c[1]) == g.findLabel(c[2]))
                result[result_length] = true;
        } else { // cut
            g.unionElements(c[1], c[2]);
        }
    }

    std::stringstream sout;

    for (int i = 0; i < result.size(); ++i)
        sout << (result[i] ? "YES" : "NO") << "\n";

    std::cout << sout.str();

    return 0;
}
