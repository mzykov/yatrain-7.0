#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

std::pair<int, std::vector<int>> get_distribution(std::vector<std::pair<int, int>>& x, std::vector<std::pair<int, int>>& y) {
    std::stable_sort(x.begin(), x.end());
    std::stable_sort(y.begin(), y.end());

    int xp = 0, yp = 0;
    std::vector<int> distr(x.size(), 0);

    while (xp < x.size() && yp < y.size()) {
        if (std::get<0>(y[yp]) > std::get<0>(x[xp])) {
            distr[std::get<1>(x[xp])] = std::get<1>(y[yp]);
            ++xp;
        }
        ++yp;
    }

    return { xp, distr };
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> x(n), y(m);

    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        x[i] = { val, i };
    }

    for (int i = 0; i < m; ++i) {
        int val;
        std::cin >> val;
        y[i] = { val, i + 1 };
    }

    const auto& [p, distr] = get_distribution(x, y);

    std::cout << p << "\n";

    for (int n : distr)
        std::cout << n << " ";

    std::cout << "\n";

    return 0;
}
