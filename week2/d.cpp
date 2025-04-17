#include <iostream>
#include <string>
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
        return RangeMaximumQueryRec(0, 0, n_ - 1, std::max(0, ql), std::min(n_ - 1, qr));
    }

    void UpdateValue(int index, int new_value) {
        int new_value_index = n_ - 1 + index;
        std::get<0>(v_[new_value_index]) = new_value;
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
        is >> std::get<0>(rtree.v_[pos]);
        std::get<1>(rtree.v_[pos]) = pos - rtree.n_ + 2;
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
        return std::max(left, right);
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
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "s") {
            int l, r;
            std::cin >> l >> r;
            const auto& [max_value, _] = rtree.RangeMaximumQuery(l - 1, r - 1);
            std::cout << max_value << " ";
        } else {
            int i, new_value;
            std::cin >> i >> new_value;
            rtree.UpdateValue(i - 1, new_value);
        }
    }

    return 0;
}
