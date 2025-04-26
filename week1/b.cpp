#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;

        std::vector<int> res;
        int curr_min = n;
        int curr_len = 0;

        while (n--) {
            int k;
            std::cin >> k;

            if (std::min(k, curr_min) >= curr_len + 1) {
                curr_min = std::min(k, curr_min);
                ++curr_len;
            } else {
                res.push_back(curr_len);
                curr_min = k;
                curr_len = 1;
            }
        }
        res.push_back(curr_len);

        std::cout << res.size() << "\n";

        for (int n : res)
            std::cout << n << " ";

        std::cout << "\n";
    }

    return 0;
}
