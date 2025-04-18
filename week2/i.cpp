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
    RangeTree(int n) : n_(nearest_power2(n)), last_pos_(n_-2), v_(std::vector<std::vector<unsigned long>>(2*n_-1, { 0, 0 })) {}

    void Build() {
        for (int i = v_.size()/2 - 1; i >= 0; --i)
            v_[i] = mergeRanges(v_[2*i + 1], v_[2*i + 2]);
    }

    unsigned long RangeMaximumQuery(int ql, int qr) {
        const auto res = rangeMaximumQueryRec(0, 0, n_ - 1, ql, qr);
        return res[0];
    }

    void UpdateRange(int ql, int qr, unsigned long add) {
        updateRangeRec(0, 0, n_ - 1, ql, qr, add);
    }

    friend std::istream& operator>>(std::istream& is, RangeTree& rtree) {
        unsigned long val;
        is >> val;
        int pos = rtree.nextPosition();
        rtree.v_[pos][0] = val;
        return is;
    }

private:
    int n_;
    int last_pos_;
    std::vector<std::vector<unsigned long>> v_;

    inline int nextPosition() {
        ++last_pos_;
        return last_pos_;
    }

    inline std::vector<unsigned long> mergeRanges(const std::vector<unsigned long> &left, const std::vector<unsigned long> &right) const {
        return std::max(left, right);
    }

    std::vector<unsigned long> rangeMaximumQueryRec(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return { 0, 0 };
        } else if (ql <= l && r <= qr) {
            return v_[i];
        } else {
            if (v_[i][1] != 0) {
                if (2*i + 2 < v_.size()) {
                    v_[2*i + 1][0] += v_[i][1];
                    v_[2*i + 1][1] += v_[i][1];
                    v_[2*i + 2][0] += v_[i][1];
                    v_[2*i + 2][1] += v_[i][1];
                }
                v_[i][1] = 0;
            }
            int mid = (l + r)/2;
            auto left  = rangeMaximumQueryRec(2*i + 1, l, mid, ql, qr);
            auto right = rangeMaximumQueryRec(2*i + 2, mid + 1, r, ql, qr);
            return mergeRanges(left, right);
        }
    }

    std::vector<unsigned long> updateRangeRec(int i, int l, int r, int ql, int qr, unsigned long add) {
        if (r < ql || l > qr) {
            return v_[i];
        } else if (ql <= l && r <= qr) {
            v_[i][0] += add;
            v_[i][1] += add;
            return v_[i];
        } else {
            if (v_[i][1] != 0) {
                if (2*i + 2 < v_.size()) {
                    v_[2*i + 1][0] += v_[i][1];
                    v_[2*i + 1][1] += v_[i][1];
                    v_[2*i + 2][0] += v_[i][1];
                    v_[2*i + 2][1] += v_[i][1];
                }
                v_[i][1] = 0;
            }
            int mid = (l + r)/2;
            const auto left  = updateRangeRec(2*i + 1, l, mid, ql, qr, add);
            const auto right = updateRangeRec(2*i + 2, mid + 1, r, ql, qr, add);
            const auto best  = mergeRanges(left, right);
            v_[i][0] = best[0];
            return v_[i];
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
        int l, r;
        std::cin >> cmd >> l >> r;
        --l; --r;

        if (cmd == "a") {
            unsigned long add;
            std::cin >> add;
            if (add != 0)
                rtree.UpdateRange(l, r, add);
        } else {
            std::cout << rtree.RangeMaximumQuery(l, r) << " ";
        }
    }

    std::cout << "\n";

    return 0;
}
