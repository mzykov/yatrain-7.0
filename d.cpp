#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

std::pair<int, std::vector<char>> maximum_cost_route(std::vector<std::vector<int>>& mat) {
    int n = mat.size() - 1, m = mat[0].size() - 1;
    std::vector<char> reversed_route;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            mat[i][j] += std::max(mat[i][j - 1], mat[i - 1][j]);

    for (int i = n, j = m; i + j > 2; ) {
        if (i == 1) {
            reversed_route.push_back('R');
            --j;
        } else if (j == 1) {
            reversed_route.push_back('D');
            --i;
        } else if (mat[i - 1][j] > mat[i][j - 1]) {
            reversed_route.push_back('D');
            --i;
        } else {
            reversed_route.push_back('R');
            --j;
        }
    }

    return { mat[n][m], reversed_route };
}

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> mat(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            std::cin >> mat[i][j];

    auto [max_cost, reversed_route] = maximum_cost_route(mat);
    std::cout << max_cost << "\n";

    while (!reversed_route.empty()) {
        std::cout << reversed_route.back() << " ";
        reversed_route.pop_back();
    }

    std::cout << "\n";

    return 0;
}
