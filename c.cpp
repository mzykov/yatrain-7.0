#include <algorithm>
#include <iostream>
#include <vector>

int reduced_length(std::vector<int>& positions) {
    sort(positions.begin(), positions.end());

    constexpr int far_away = 20001;
    int right = far_away, res = 0;

    while (!positions.empty()) {
        int center = positions.back();
        positions.pop_back();
        int left = -far_away;

        if (!positions.empty())
            left = positions.back();

        int rhs = right - center;
        int lhs = center - left;

        if (rhs > lhs) {
            res += lhs;
            right = left;
            if (!positions.empty())
                positions.pop_back();
        } else {
            res += rhs;
            right = center;
        }
    }

    return res;
}

int main() {
    int n = 1;
    std::cin >> n;

    std::vector<int> positions;

    while (n--) {
        int pos;
        std::cin >> pos;
        positions.push_back(pos);
    }

    std::cout << reduced_length(positions) << "\n";

    return 0;
}
