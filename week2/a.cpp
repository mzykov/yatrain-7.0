#include <iostream>
#include <vector>
#include <utility>

int nearest_power2(int n) {
    int res = 1;
    while (res < n)
        res <<= 1;
    return res;
}

class RangeTree {
public:
    RangeTree(int n) : n_(nearest_power2(n)), last_pos_(n_-2), v_(std::vector<std::pair<int,int>>(2*n_-1, { 0, 0 })) {}

    void Build() {
        for (int i = v_.size()/2 - 1; i >= 0; --i)
            v_[i] = mergeRanges(v_[2*i + 1], v_[2*i + 2]);
    }

    std::pair<int,int> RangeMaximumQuery(int ql, int qr) {
        return RangeMaximumQueryRec(0, 0, n_ - 1, std::max(0, ql), std::min(n_-1, qr));
    }

    friend std::istream& operator>>(std::istream& is, RangeTree& rtree) {
        int pos = rtree.nextPosition();
        is >> std::get<0>(rtree.v_[pos]);
        std::get<1>(rtree.v_[pos]) = 1;
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
        std::pair<int,int> res;
        auto [lv, lc] = left;
        auto [rv, rc] = right;
        if (lv > rv) {
            res = left;
        } else if (lv < rv) {
            res = right;
        } else {
            res = { lv, lc + rc };
        }
        return res;
    }

    std::pair<int,int> RangeMaximumQueryRec(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return { 0, 0 };
        } else if (l == ql && r == qr) {
            return v_[i];
        } else {
            int mid = (l + r)/2;
            std::pair<int,int> left = { 0, 0 }, right = { 0, 0 };

            if (ql <= mid) {
                left = RangeMaximumQueryRec(2*i + 1, l, mid, ql, std::min(mid, qr));
            }
            if (qr > mid) {
                right = RangeMaximumQueryRec(2*i + 2, mid + 1, r, std::max(mid + 1, ql), qr);
            }

            return mergeRanges(left, right);
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

    int k;
    std::cin >> k;

    while (k--) {
        int l, r;
        std::cin >> l >> r;
        const auto& [max_val, max_count] = rtree.RangeMaximumQuery(l - 1, r - 1);
        std::cout << max_val << " " << max_count << "\n";
    }

    return 0;
}
