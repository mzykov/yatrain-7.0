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

    unsigned long GetElementByIndex(int index) {
        return getElementByIndexRec(0, 0, n_ - 1, index);
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

    unsigned long getElementByIndexRec(int i, int l, int r, int index) {
        if (v_[i][1] != 0) {
            unsigned long add = v_[i][1];
            v_[i][1] = 0UL;
            v_[i][0] += add;
            if (2*i + 2 < v_.size()) {
                v_[2*i + 1][1] += add;
                v_[2*i + 2][1] += add;
            }
        }
        if (l == r && l == index) {
            return v_[i][0];
        } else {
            int mid = (l + r)/2;

            if (index <= mid)
                return getElementByIndexRec(2*i + 1, l, mid, index);
            else
                return getElementByIndexRec(2*i + 2, mid + 1, r, index);
        }
    }

    void updateRangeRec(int i, int l, int r, int ql, int qr, unsigned long add) {
        if (r < ql || l > qr) {
            return;
        } else if (l == ql && r == qr) {
            v_[i][1] += add;
            return;
        } else {
            int mid = (l + r)/2;

            if (ql <= mid) {
                updateRangeRec(2*i + 1, l, mid, ql, std::min(mid, qr), add);
            }
            if (qr > mid) {
                updateRangeRec(2*i + 2, mid + 1, r, std::max(mid + 1, ql), qr, add);
            }
            return;
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

        if (cmd == "a") {
            int l, r;
            unsigned long add;
            std::cin >> l >> r >> add;
            if (add != 0)
                rtree.UpdateRange(l - 1, r - 1, add);
        } else {
            int i;
            std::cin >> i;
            std::cout << rtree.GetElementByIndex(i - 1) << "\n";
        }
    }

    return 0;
}
