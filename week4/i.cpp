#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    unsigned long total = 0;
    std::vector<std::vector<unsigned long>> snowballs(n + 1); // [ [top, prev, total], ... ]
    snowballs[0] = {0, 0, 0};

    for (int i = 1; i <= n; ++i) {
        unsigned long t, m;
        std::cin >> t >> m;

        snowballs[i] = { 0, t, snowballs[t][2] };

        if (m == 0) {
            const auto &pprev = snowballs[snowballs[t][1]];
            snowballs[i][0] = pprev[0];
            snowballs[i][1] = pprev[1];
            snowballs[i][2] = pprev[2];
        } else {
            snowballs[i][0] += m;
            snowballs[i][2] += m;
        }

        total += snowballs[i][2];
    }

    std::cout << total << "\n";

    return 0;
}
