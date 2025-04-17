#include <iostream>
#include <string>
#include <vector>
#include <utility>

int nearest_power2(int n) {
    int res = 2;
    while (res < n)
        res <<= 1;
    return res;
}

class RangeTree {
public:
    RangeTree(int n) : n_(nearest_power2(n)), last_pos_(n_-2), v_(std::vector<std::pair<int,int>>(2*n_-1, { -1, 0 })) {}

    void Build() {
        for (int i = v_.size()/2 - 1; i >= 0; --i)
            v_[i] = mergeRanges(v_[2*i + 1], v_[2*i + 2]);
    }

    int RangeKZeroIndexQuery(int ql, int qr, int k) {
        if (ql > 0) {
            const auto& [_, zeros_count] = rangeZerosCountQueryRec(0, 0, n_ - 1, 0, ql - 1);
            k += zeros_count;
        }

        int kzero_index = PrefixKZeroIndexQuery(k);

        if (kzero_index > qr || kzero_index < ql)
            return -1;
        else
            return kzero_index + 1;
    }

    int PrefixKZeroIndexQuery(int k) {
        return prefixKZeroIndexQueryRec(0, k);
    }

    void UpdateValue(int index, int new_value) {
        int new_value_index = n_ - 1 + index;
        std::get<0>(v_[new_value_index]) = new_value > 0;
        std::get<1>(v_[new_value_index]) = new_value == 0;
        int i = (new_value_index - 1)/2;

        while (true) {
            v_[i] = mergeRanges(v_[2*i + 1], v_[2*i + 2]);
            if (i == 0)
                break;
            else
                i = (i - 1)/2;
        }
    }

    friend std::istream& operator>>(std::istream& is, RangeTree& rtree) {
        int pos = rtree.nextPosition();
        int val;
        is >> val;
        std::get<0>(rtree.v_[pos]) = val > 1;
        std::get<1>(rtree.v_[pos]) = val == 0;
        return is;
    }

private:
    int n_;
    int last_pos_;
    std::vector<std::pair<int,int>> v_;

    inline int nextPosition() {
        ++last_pos_;
        return last_pos_;
    }

    inline std::pair<int,int> mergeRanges(const std::pair<int,int> &left, const std::pair<int,int> &right) const {
        auto [lv, lc] = left;
        auto [rv, rc] = right;
        return { std::max(lv, rv), lc + rc };
    }

    std::pair<int,int> rangeZerosCountQueryRec(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return { -1, 0 };
        } else if (l == ql && r == qr) {
            return v_[i];
        } else {
            int mid = (l + r)/2;
            std::pair<int,int> left = { -1, 0 }, right = { -1, 0 };

            if (ql <= mid) {
                left = rangeZerosCountQueryRec(2*i + 1, l, mid, ql, std::min(mid, qr));
            }
            if (qr > mid) {
                right = rangeZerosCountQueryRec(2*i + 2, mid + 1, r, std::max(mid + 1, ql), qr);
            }

            return mergeRanges(left, right);
        }
    }

    int prefixKZeroIndexQueryRec(int i, int k) {
        const int zeros_count = std::get<1>(v_[i]);

        if (k > zeros_count) {
            return -1;
        }

        if (2*i + 1 < v_.size()) {
            const int left_count = std::get<1>(v_[2*i + 1]);

            if (left_count >= k)
                return prefixKZeroIndexQueryRec(2*i + 1, k);
            else
                return prefixKZeroIndexQueryRec(2*i + 2, k - left_count);
        } else if (std::get<0>(v_[i]) == 0) {
            return i - n_ + 1;
        } else {
            return -1;
        }
    }
};

int main() {
    int n;
    std::cin >> n;

    RangeTree rtree(n);

    while (n--)
        std::cin >> rtree;

    rtree.Build();

    int m;
    std::cin >> m;

    while (m--) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "s") {
            int l, r, k;
            std::cin >> l >> r >> k;
            int kzero_index = rtree.RangeKZeroIndexQuery(l - 1, r - 1, k);
            std::cout << kzero_index << " ";
        } else {
            int i, new_value;
            std::cin >> i >> new_value;
            rtree.UpdateValue(i - 1, new_value);
        }
    }

    return 0;
}
