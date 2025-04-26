#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

int count_bits(unsigned long long v) {
    int count = 0;
    while (v) {
        if (v & 1)
            ++count;
        v >>= 1;
    }
    return count;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::pair<int, unsigned long long>> a(n);
    int total_bits = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> std::get<1>(a[i]);
        std::get<0>(a[i]) = count_bits(std::get<1>(a[i]));
        total_bits += std::get<0>(a[i]);
    }

    if (total_bits % 2) {
        std::cout << "impossible\n";
        return 0;
    }

    std::sort(a.rbegin(), a.rend());

    std::vector<unsigned long long> b(n, 0);

    for (int num : b)
        std::cout << num << " ";

    std::cout << "\n";

    return 0;
}
