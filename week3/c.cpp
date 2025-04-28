#include <algorithm>
#include <iostream>
#include <vector>

int count_ones(unsigned long long num) {
    int count = 0;
    while (num) {
        if (num & 1)
            ++count;
        num >>= 1;
    }
    return count;
}

int get_length_in_bits(unsigned long long num) {
    int count = 0;
    while (num) {
        num >>= 1;
        ++count;
    }
    return count;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n, {0, 0, 0});
    int max_len = 0;

    for (int i = 0; i < n; ++i) {
        unsigned long long num;
        std::cin >> num;
        a[i][0] = count_ones(num);
        a[i][2] = i;
        max_len = std::max(max_len, get_length_in_bits(num));
    }

    for (auto& v : a)
        v[1] = max_len - v[0];

    std::vector<unsigned long long> b(n, 0);

    for (int l = 0; l < max_len; ++l) {
        std::sort(a.rbegin(), a.rend());

        unsigned int ksum = 0;
        int last_one = -1;

        for (int i = 0; i < (a.size()/2)*2; ++i) {
            if (a[i][0] > 0) {
                --a[i][0];
                ksum = (ksum + 1) % 2;
                b[a[i][2]] |= 1;
                last_one = i;
            } else {
                --a[i][1];
            }
            if (l < max_len - 1)
                b[a[i][2]] <<= 1;
        }

        if (a.size() % 2 == 1) {
            if (ksum == 0 && a.back()[1] > 0) {
                --(a.back()[1]);
                b[a.back()[2]] |= 0;
                if (l < max_len - 1)
                    b[a.back()[2]] <<= 1;
            } else {
                std::cout << "impossible\n";
                return 0;
            }
        }

        if (ksum == 1 && last_one != -1) {
            ++a[last_one][0];
            ksum = 0;
            --a[last_one][1];
            if (l < max_len - 1) {
                b[a[last_one][2]] >>= 2;
                b[a[last_one][2]] <<= 2;
            }
        }
    }

    unsigned long long res = 0;
    for (unsigned long long num : b)
        res ^= num;

    if (res > 0) {
        std::cout << "impossible";
    } else {
        for (unsigned long long num : b)
            std::cout << num << " ";
    }

    std::cout << "\n";

    return 0;
}
