#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<bool> v(m + 1, false);
    v[0] = true;

    std::vector<int> weights;

    while (n--) {
        int w;
        std::cin >> w;
        weights.push_back(w);
    }

    std::sort(weights.begin(), weights.end());

    for (int w : weights) {
        for (int i = m - w; i >= 0; --i) {
            if (v[i] == true) {
                v[i + w] = true;
            }
        }
    }

    std::cout << std::distance(std::find(v.rbegin(), v.rend(), true), v.rend()) - 1 << "\n";

    return 0;
}
