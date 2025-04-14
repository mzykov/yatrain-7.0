#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

std::vector<bool> available_lengths(const std::vector<std::pair<int,int>>& lengths, int maxlen) {
    std::vector<bool> res(maxlen + 1, false);
    res[0] = true;
    for (const auto& [len, _] : lengths)
        for (int i = maxlen - len; i >= 0; --i)
            if (res[i] == true)
                res[i + len] = true;
    return res;
}

void intersect_pair_lines(const std::vector<bool>& from, std::vector<bool>& to) {
    for (int i = 0; i < to.size(); ++i)
        to[i] = to[i] && from[i];
}

std::vector<bool> intersect_all_lines(const std::vector<std::vector<std::pair<int,int>>>& colors, int maxlen) {
    std::vector<bool> intersection(maxlen + 1, true);
    for (int i = 1; i < colors.size(); ++i) {
        auto line = available_lengths(colors[i], maxlen);
        intersect_pair_lines(line, intersection);
    }
    return intersection;
}

std::vector<int> stones_for_color(const std::vector<std::pair<int,int>>& mc, int m) {
    std::vector<int> res;

    std::vector<std::vector<std::pair<int,int>>> steps(1, std::vector<std::pair<int,int>>(m + 1, { -1, -1 }));
    std::get<0>(steps[0][0]) = 0;
    std::get<1>(steps[0][0]) = 0;

    for (int no = 0; no < mc.size(); ++no) {
        int w = std::get<0>(mc[no]);
        int c = w;

        steps.push_back(steps.back());
        auto& step = steps.back();

        for (int i = m - w; i >= 0; --i) {
            const int cost = std::get<0>(step[i]);
            if (cost < 0) continue;

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
            res.push_back(i);
        } else {
            break;
        }
    }

    return res;
}

int main() {
    int n, k;
    std::cin >> n >> k;

    int maxlen = 0;
    std::vector<std::vector<std::pair<int,int>>> colors(k + 1);

    {
        std::vector<int> total_lengths(k + 1, 0);

        for (int i = 1; i <= n; ++i) {
            int len, color;
            std::cin >> len >> color;
            colors[color].push_back({ len, i });
            total_lengths[color] += len;
            maxlen = std::max(maxlen, total_lengths[color]);
        }
    }

    int length_of_first_wall = 0;
    {
        auto intersection = intersect_all_lines(colors, maxlen);

        if (std::count(std::next(intersection.begin()), intersection.end(), true) < 2) {
            std::cout << "NO\n";
            return 0;
        }

        length_of_first_wall = std::distance(intersection.begin(), std::find(std::next(intersection.begin()), intersection.end(), true));
    }

    std::vector<int> first_wall_stones;

    for (int i = 1; i < colors.size(); ++i) {
        std::sort(colors[i].rbegin(), colors[i].rend());
        auto stones = stones_for_color(colors[i], length_of_first_wall);
        for (int j : stones) {
            std::get<0>(colors[i][j]) = maxlen + 1; // delete element
            first_wall_stones.push_back(std::get<1>(colors[i][j]));
        }
    }

    {
        auto intersection = intersect_all_lines(colors, maxlen);

        if (std::count(std::next(intersection.begin()), intersection.end(), true) == 0) {
            std::cout << "NO\n";
            return 0;
        }
    }

    std::cout << "YES\n";

    for (int no : first_wall_stones)
        std::cout << no << " ";
    std::cout << "\n";

    return 0;
}
