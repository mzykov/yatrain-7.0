#include <iostream>
#include <limits>
#include <string>
#include <vector>

int nearest_power2(int n) {
    int res = 2;
    while (res < n)
        res <<= 1;
    return res;
}

constexpr unsigned long long largest = 1000000ULL;

class RangeTree {
public:
    RangeTree(int n) :
        n_(nearest_power2(n)),
        last_pos_(n_-2),
        v_(std::vector<std::vector<unsigned long long>>(2*n_-1, { 0ULL, 0ULL, largest })),
        x_(37ULL),
        modulo_(std::numeric_limits<unsigned long long>::max()),
        xp_(std::vector<unsigned long long>(n_, 0ULL)),
        xp_sum_(std::vector<unsigned long long>(n_, 0ULL)) {

        xp_[0] = 1ULL;
        for (int i = 1; i < n_; ++i)
            xp_[i] = (xp_[i-1] * x_) % modulo_;

        xp_sum_[0] = xp_[0];
        for (int i = 1; i < n_; ++i)
            xp_sum_[i] = (xp_[i] + xp_sum_[i-1]) % modulo_;
    }

    void Build() {
        for (int i = v_.size()/2 - 1; i >= 0; --i)
            v_[i] = mergeRanges(v_[2*i + 1], v_[2*i + 2]);
    }

    char RangeEqualityQuery(int ql, int qr, int k) {
        auto left  = rangeHashQueryRec(0, 0, n_ - 1, ql, ql + k - 1);
        auto right = rangeHashQueryRec(0, 0, n_ - 1, qr, qr + k - 1);
        auto shifted = (left[1] * xp_[qr - ql]) % modulo_;
        return shifted == right[1] ? '+' : '-';
    }

    void UpdateRange(int ql, int qr, unsigned long long k) {
        updateRangeRec(0, 0, n_ - 1, ql, qr, k);
    }

    friend std::istream& operator>>(std::istream& is, RangeTree& rtree) {
        unsigned long long val;
        is >> val;
        int pos = rtree.nextPosition();
        int index = pos - rtree.n_ + 1;
        rtree.v_[pos][0] = val;
        rtree.v_[pos][1] = (val * rtree.xp_[index]) % rtree.modulo_; // hash
        return is;
    }

private:
    int n_, last_pos_;
    unsigned long long x_, modulo_;
    std::vector<std::vector<unsigned long long>> v_;
    std::vector<unsigned long long> xp_, xp_sum_;

    inline int nextPosition() {
        ++last_pos_;
        return last_pos_;
    }

    unsigned long long recalcHash(unsigned long long value, int l, int r) {
        unsigned long long res = xp_sum_[r];
        if (l > 0)
            res -= xp_sum_[l - 1];
        return (value * res) % modulo_;
    }

    inline std::vector<unsigned long long> mergeRanges(const std::vector<unsigned long long> &left, const std::vector<unsigned long long> &right) const {
        std::vector<unsigned long long> res = { 0ULL, 0ULL, largest };
        res[0] = std::max(left[0], right[0]);
        res[1] = (left[1] + right[1]) % modulo_;
        return res;
    }

    std::vector<unsigned long long> rangeHashQueryRec(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return { 0ULL, 0ULL, largest };
        } else if (ql <= l && r <= qr) {
            return v_[i];
        } else {
            int mid = (l + r)/2;
            if (v_[i][2] != largest) { // has promise
                if (2*i + 2 < v_.size()) {
                    v_[2*i + 1][0] = v_[i][2];                         // left value
                    v_[2*i + 1][1] = recalcHash(v_[i][2], l, mid);     // left hash
                    v_[2*i + 1][2] = v_[i][2];                         // left promise
                    v_[2*i + 2][0] = v_[i][2];                         // right value
                    v_[2*i + 2][1] = recalcHash(v_[i][2], mid + 1, r); // right hash
                    v_[2*i + 2][2] = v_[i][2];                         // right promise
                }
                v_[i][2] = largest; // remove promise
            }
            auto left  = rangeHashQueryRec(2*i + 1, l, mid, ql, qr);
            auto right = rangeHashQueryRec(2*i + 2, mid + 1, r, ql, qr);
            return mergeRanges(left, right);
        }
    }

    std::vector<unsigned long long> updateRangeRec(int i, int l, int r, int ql, int qr, unsigned long long k) {
        if (r < ql || l > qr) {
            return v_[i];
        } else if (ql <= l && r <= qr) {
            v_[i][0] = k;
            v_[i][1] = recalcHash(k, l, r);
            v_[i][2] = k;
            return v_[i];
        } else {
            int mid = (l + r)/2;
            if (v_[i][2] != largest) { // has promise
                if (2*i + 2 < v_.size()) {
                    v_[2*i + 1][0] = v_[i][2];                         // left value
                    v_[2*i + 1][1] = recalcHash(v_[i][2], l, mid);     // left hash
                    v_[2*i + 1][2] = v_[i][2];                         // left promise
                    v_[2*i + 2][0] = v_[i][2];                         // right value
                    v_[2*i + 2][1] = recalcHash(v_[i][2], mid + 1, r); // right hash
                    v_[2*i + 2][2] = v_[i][2];                         // right promise
                }
                v_[i][2] = largest; // remove promise
            }
            const auto left  = updateRangeRec(2*i + 1, l, mid, ql, qr, k);
            const auto right = updateRangeRec(2*i + 2, mid + 1, r, ql, qr, k);
            v_[i] = mergeRanges(left, right);
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
        int cmd, l, r;
        unsigned long long k;
        std::cin >> cmd >> l >> r >> k;
        --l; --r;

        if (cmd == 0)
            rtree.UpdateRange(l, r, k);
        else
            std::cout << rtree.RangeEqualityQuery(std::min(l, r), std::max(l, r), k);
    }

    std::cout << "\n";

    return 0;
}
