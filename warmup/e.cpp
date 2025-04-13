#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

struct TotalCost {
    int total = 0;
    int unused_coupons = 0;
    std::vector<int> coupon_days;
};

using TotalCostPtr = std::shared_ptr<TotalCost>;

auto min_cost(const TotalCostPtr a, const TotalCostPtr b) {
    if (a && b) {
        if (a->total < b->total)
            return a;
        else if (b->total < a->total)
            return b;
        else if (a->unused_coupons > b->unused_coupons)
            return a;
        else
            return b;
    } else if (a != nullptr) {
        return a;
    } else {
        return b;
    }
}

void buy_dinner_using_coupon(const int day, const int cost, TotalCost prev, std::vector<TotalCostPtr>& dp) {
    prev.coupon_days.push_back(day);
    prev.unused_coupons -= 1;
    dp[prev.unused_coupons] = min_cost(dp[prev.unused_coupons], std::make_shared<TotalCost>(prev.total, prev.unused_coupons, prev.coupon_days));
}

inline int achieve_coupon(const int cost) {
    constexpr int min_cost = 100;
    return cost > min_cost;
}

void buy_dinner_using_money(const int day, const int cost, TotalCost prev, std::vector<TotalCostPtr>& dp) {
    prev.total += cost;
    prev.unused_coupons += achieve_coupon(cost);

    while (dp.size() < prev.unused_coupons + 1)
        dp.push_back(nullptr);

    dp[prev.unused_coupons] = min_cost(dp[prev.unused_coupons], std::make_shared<TotalCost>(prev.total, prev.unused_coupons, prev.coupon_days));
}

auto find_min(std::vector<TotalCostPtr>& v) {
    auto& res = v[0];

    for (int i = 1; i < v.size(); ++i)
        res = min_cost(res, v[i]);

    return res;
}

auto reduced_cost(const std::vector<int>& costs) {
    auto empty_ptr = std::make_shared<TotalCost>();

    if (costs.empty())
        return empty_ptr;

    std::vector<TotalCostPtr> dp;
    constexpr int first_day = 1;

    buy_dinner_using_money(first_day, costs[0], *empty_ptr, dp);

    for (int i = 1; i < costs.size(); ++i) {
        std::vector<TotalCostPtr> next_dp(dp.size(), nullptr);

        for (int unused_coupons = 0; unused_coupons < dp.size(); ++unused_coupons) {
            auto p = dp[unused_coupons];

            if (p == nullptr)
                continue;

            const int day = i + 1;

            if (unused_coupons > 0) {
                buy_dinner_using_coupon(day, costs[i], *p, next_dp);
            }

            buy_dinner_using_money(day, costs[i], *p, next_dp);
        }

        dp = next_dp;
    }

    return find_min(dp);
}

void print_result(TotalCostPtr p) {
    std::cout << p->total << "\n";
    std::cout << p->unused_coupons << " " << p->coupon_days.size() << "\n";

    for (int day : p->coupon_days)
        std::cout << day << " ";

    if (p->coupon_days.size() > 0)
        std::cout << "\n";
}

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<int> costs;

    while (n--) {
        int cost = 0;
        std::cin >> cost;
        costs.push_back(cost);
    }

    print_result(reduced_cost(costs));

    return 0;
}
