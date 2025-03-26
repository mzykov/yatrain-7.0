#include <iostream>
#include <vector>

// n > 4: R(n) = 2 * R(n - 1) - R(n - 4)
int count_strings_with_no_three_consecutive_ones(int n) {
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
    int n = 1;
    std::cin >> n;
    std::cout << count_strings_with_no_three_consecutive_ones(n) << "\n";
    return 0;
}
