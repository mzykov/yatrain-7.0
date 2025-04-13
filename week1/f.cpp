#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<std::pair<int,int>>> steps(1, std::vector<std::pair<int,int>>(m + 1, { -1, -1 }));
    std::get<0>(steps[0][0]) = 0;
    std::get<1>(steps[0][0]) = 0;

    std::vector<std::pair<int,int>> mc(n);

    for (int i = 0; i < n; ++i)
        std::cin >> std::get<0>(mc[i]);

    for (int i = 0; i < n; ++i)
        std::cin >> std::get<1>(mc[i]);

    for (int no = 0; no < n; ++no) {
        int w = std::get<0>(mc[no]);
        int c = std::get<1>(mc[no]);

        steps.push_back(steps.back());
        auto& step = steps.back();

        for (int i = m - w; i >= 0; --i) {
            const int cost = std::get<0>(step[i]);
            if (cost < 0)
                continue;

            if (cost + c > std::get<0>(step[i + w])) {
                std::get<0>(step[i + w]) = cost + c;
                std::get<1>(step[i + w]) = no;
            }
        }
    }

    int i = steps.size() - 1;
    int curr_weight = 0;

    while (i > 0) {
        auto& step = steps[i];
        const auto& e = *std::max_element(step.rbegin() + curr_weight, step.rend());
        int last_cost = std::get<0>(e);
        if (last_cost > 0) {
            i = std::get<1>(e);
            curr_weight += std::get<0>(mc[i]);
            std::cout << i + 1 << "\n";
        } else {
            break;
        }
    }

    return 0;
}
