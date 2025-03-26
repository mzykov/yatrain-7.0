#include <iostream>
#include <vector>

int reduced_time(std::vector<std::vector<int>>& times) {
    constexpr int max_duration = 3600;
    std::vector<int> dp(3, max_duration);
    q[0] = 0;

    while (!times.empty()) {
        const auto& curr = times.back();
        int t_next = min({ curr[0] + dp[0], curr[1] + dp[1], curr[2] + dp[2] });
        dp.insert(dp.begin(), t_next);
        dp.pop_back();
        times.pop_back();
    }

    return dp[0];
}

int main() {
    int n = 1;
    std::cin >> n;

    vector<vector<int>> times;

    while (n--) {
        int a, b, c;
        std::cin >> a >> b >> c;
        times.push_back({ a, b, c });
    }

    std::cout << reduced_time(times) << "\n";

    return 0;
}
