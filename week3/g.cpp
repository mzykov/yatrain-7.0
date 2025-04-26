#include <iostream>
#include <string>
#include <vector>

int nearest_power2(int n) {
    int res = 2;
    while (res < n)
        res <<= 1;
    return res;
}

class RangeTree {
public:
    RangeTree(int n) : n_(nearest_power2(n)), v_(std::vector<unsigned long long>(2*n_-1, 0)) {}

    unsigned long long RangeSumQuery(int ql, int qr) {
        return RangeSumQueryRec(0, 0, n_ - 1, ql, qr);
    }

    void UpdateValue(int index, unsigned long long new_value) {
        int new_value_index = n_ - 1 + index;
        v_[new_value_index] = new_value;
        int i = (new_value_index - 1)/2;

        while (true) {
            v_[i] = mergeRanges(v_[2*i + 1], v_[2*i + 2]);
            if (i == 0)
                break;
            else
                i = (i - 1)/2;
        }
    }

private:
    int n_;
    std::vector<unsigned long long> v_;

    inline unsigned long long mergeRanges(const unsigned long long left, const unsigned long long right) const {
        return left + right;
    }

    unsigned long long RangeSumQueryRec(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return 0;
        } else if (ql <= l && r <= qr) {
            return v_[i];
        } else {
            int mid = (l + r)/2;
            unsigned long long left = 0, right = 0;

            if (ql <= mid) {
                left = RangeSumQueryRec(2*i + 1, l, mid, ql, qr);
            }
            if (qr > mid) {
                right = RangeSumQueryRec(2*i + 2, mid + 1, r, ql, qr);
            }

            return mergeRanges(left, right);
        }
    }
};

int main() {
    int n, k;
    std::cin >> n >> k;

    RangeTree rtree(n);

    while (k--) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "Q") {
            int l, r;
            std::cin >> l >> r;
            std::cout << rtree.RangeSumQuery(l - 1, r - 1) << "\n";
        } else {
            int i, new_value;
            std::cin >> i >> new_value;
            rtree.UpdateValue(i - 1, new_value);
        }
    }

    return 0;
}
