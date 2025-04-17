#include <iostream>
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
    RangeTree(int n) : n_(nearest_power2(n)), last_pos_(n_-2), v_(std::vector<std::pair<int,int>>(2*n_-1, { -1, -1 })) {}

    void Build() {
        for (int i = v_.size()/2 - 1; i >= 0; --i)
            v_[i] = mergeRanges(v_[2*i + 1], v_[2*i + 2]);
    }

    int RightNearestGreatestValue(int index, int x) {
        const auto& [_, k] = rightNearestGreatestValueRec(0, 0, n_ - 1, index, x);
        return k;
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

    std::pair<int,int> rightNearestGreatestValueRec(int i, int l, int r, int index, int x) {
        int val = std::get<0>(v_[i]);

        if (x > val || r < index) {
            return { -1, -1 };
        }
        if (2*i + 1 < v_.size()) {
            int mid = (l + r)/2;
            std::pair<int,int> left = { -1, -1 }, right = { -1, -1 };

            const int left_max = std::get<0>(v_[2*i + 1]);
            if (left_max >= x && index <= mid) {
                left = rightNearestGreatestValueRec(2*i + 1, l, mid, index, x);
            }
            if (std::get<0>(left) < 0) {
                const int right_max = std::get<0>(v_[2*i + 2]);
                if (right_max >= x && index <= r) {
                    return rightNearestGreatestValueRec(2*i + 2, mid + 1, r, index, x);
                }
            } else {
                return left;
            }
        } else {
            return v_[i];
        }
        return { -1, -1 };
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    RangeTree rtree(n);

    while (n--)
        std::cin >> rtree;

    rtree.Build();

    while (m--) {
        int t, i, x;
        std::cin >> t >> i >> x;
        --i;

        if (t == 1) {
            int k = rtree.RightNearestGreatestValue(i, x);
            std::cout << k << "\n";
        } else {
            rtree.UpdateValue(i, x);
        }
    }

    return 0;
}
