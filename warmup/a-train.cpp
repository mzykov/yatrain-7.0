#include <bitset>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#include <limits>

int generate_rec(unsigned long curr, int ones, int rem) {
    if (rem == 0)
        return 1;

    curr <<= 1;
    int res = generate_rec(curr, 0, rem - 1);

    if (ones < 2)
        res += generate_rec(curr + 1, ones + 1, rem - 1);

    return res;
}

inline unsigned long construct_upper_limit(int n) {
    constexpr unsigned long group_len = 3, group_mask = 6;
    unsigned long res = 0;

    for (int i = n / group_len; i > 0; --i)
        res = (res << group_len) | group_mask;

    for (int i = n % group_len; i > 0; --i)
        res = (res << 1) | 1;

    return res;
}

bool has_three_consecutive_ones(unsigned long num) {
    constexpr unsigned long group_mask = 7;
    while (num > 0) {
        if ((num & group_mask) == group_mask)
            return true;
        num >>= 1;
    }
    return false;
}

int generate_linear(int n) {
    unsigned long upper_limit = construct_upper_limit(n);
    int res = 0;

    while (upper_limit > 0) {
        if (has_three_consecutive_ones(upper_limit) == false)
            ++res;
        --upper_limit;
    }
    ++res;

    return res;
}

int generate_fast(int n) {
    constexpr int forbidden_count = 3;
    std::vector<int> nums(n + 1, 0);
    nums[1] = 2;
    nums[2] = 4;
    nums[3] = 7;
    nums[4] = 13;
    for (int i = 5; i <= n; ++i)
        nums[i] = 2 * nums[i - 1] - nums[i - forbidden_count - 1];
    return nums[n];
}

int main() {
    for (int n = 1; n <= 35; ++n ) {
        int expected = generate_rec(0, 0, n);
        int got = generate_fast(n);
        if (got != expected)
            std::cerr << "N = " << n << ", Got = " << got << ", Expected = " << expected << "\n";
    }
    return 0;
}
