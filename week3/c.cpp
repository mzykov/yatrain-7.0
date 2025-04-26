#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<unsigned long long> a(n, 0);

    for (int i = 0; i < n; ++i)
        std::cin >> a[i];

    std::vector<unsigned long long> b(n, 0);

    for (int num : b)
        std::cout << num << " ";

    std::cout << "\n";

    return 0;
}
