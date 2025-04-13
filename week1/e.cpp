#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<int> v(m + 1, -1);
    v[0] = 0;

    std::vector<std::pair<int,int>> mc(n);

    for (int i = 0; i < n; ++i)
        std::cin >> std::get<0>(mc[i]);

    for (int i = 0; i < n; ++i)
        std::cin >> std::get<1>(mc[i]);

    for (const auto& [w, c] : mc)
        for (int i = m - w; i >= 0; --i)
            if (v[i] >= 0)
                v[i + w] = std::max(v[i + w], v[i] + c);

    std::cout << *max_element(v.begin(), v.end()) << "\n";

    return 0;
}
