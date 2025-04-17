#include <algorithm>
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
    RangeTree(int n) : n_(nearest_power2(n)), last_pos_(n_-2), v_(std::vector<std::vector<int>>(2*n_-1, { -1001, 0, 0, 0, 0 })) {}

    void Build() {
        for (int i = v_.size()/2 - 1; i >= 0; --i)
            v_[i] = mergeRanges(v_[2*i + 1], v_[2*i + 2]);
    }

    int LargestZerosSubseq(int ql, int qr) {
        const auto res = largestZerosSubseqRec(0, 0, n_ - 1, ql, qr);
        return res[1];
    }

    void UpdateValue(int index, int new_value) {
        int new_value_index = n_ - 1 + index;
        v_[new_value_index][0] = new_value;

        for (int j = 1; j < 5; ++j)
            v_[new_value_index][j] = new_value == 0;

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
        int val;
        is >> val;
        int pos = rtree.nextPosition();
        rtree.v_[pos][0] = val;
        for (int j = 1; j < 5; ++j)
            rtree.v_[pos][j] = val == 0;
        return is;
    }

private:
    int n_;
    int last_pos_;
    std::vector<std::vector<int>> v_;

    inline int nextPosition() {
        ++last_pos_;
        return last_pos_;
    }

    inline std::vector<int> mergeRanges(const std::vector<int> &left, const std::vector<int> &right) const {
        std::vector<int> res(5, 0);
        res[0] = std::max(left[0], right[0]); // max value
        res[1] = std::max({ left[1], right[1], left[3] + right[2] }); // max length of zeros
        if (left[4] == 1) {
            res[2] = left[2] + right[2]; // max prefix merge
        } else {
            res[2] = left[2]; // max prefix from left
        }
        if (right[4] == 1) {
            res[3] = left[3] + right[3]; // max suffix merge
        } else {
            res[3] = right[3]; // max prefix from left
        }
        res[4] = left[4] * right[4]; // only zeros
        return res;
    }

    std::vector<int> largestZerosSubseqRec(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) {
            return { -1001, 0, 0, 0, 0 };
        } else if (l == ql && r == qr) {
            return v_[i];
        } else {
            int mid = (l + r)/2;
            std::vector<int> left = { -1001, 0, 0, 0, 0 }, right = { -1001, 0, 0, 0, 0 };

            if (ql <= mid) {
                left = largestZerosSubseqRec(2*i + 1, l, mid, ql, std::min(mid, qr));
            }
            if (qr > mid) {
                right = largestZerosSubseqRec(2*i + 2, mid + 1, r, std::max(mid + 1, ql), qr);
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

    int m;
    std::cin >> m;

    while (m--) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "QUERY") {
            int l, r;
            std::cin >> l >> r;
            const int max_length = rtree.LargestZerosSubseq(l - 1, r - 1);
            std::cout << max_length << "\n";
        } else {
            int i, x;
            std::cin >> i >> x;
            rtree.UpdateValue(i - 1, x);
        }
    }

    return 0;
}
