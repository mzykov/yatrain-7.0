#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <utility>

int main() {
    unsigned long m;
    std::cin >> m;

    constexpr int sz = 31;
    std::vector<std::pair<unsigned long, unsigned long>> a(sz);

    for (int i = 0; i < sz; ++i) {
        unsigned long val;
        std::cin >> val;
        a[i] = { val, static_cast<unsigned long>(1 << i) };
    }

    auto cost_of_second = [](std::pair<unsigned long, unsigned long> v) {
        return static_cast<double>(std::get<1>(v))/std::get<0>(v);
    };

    std::sort(a.begin(), a.end(), [cost_of_second](auto a, auto b){
        return cost_of_second(a) < cost_of_second(b);
    });

    unsigned long rem_seconds = m;
    unsigned long curr_cost = 0;
    unsigned long min_cost = std::numeric_limits<unsigned long>::max();

    for (const auto& [card_seconds, card_cost] : a) {
        unsigned long num_cards = std::ceil(static_cast<double>(rem_seconds)/card_seconds);
        curr_cost += num_cards * card_cost;
        min_cost = std::min(min_cost, curr_cost);
        curr_cost -= card_cost;
        rem_seconds -= (num_cards - 1UL) * card_seconds;
    }

    std::cout << min_cost << "\n";

    return 0;
}
