#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int num;
            std::cin >> num;

            if (i != j) {
                a[i] |= num;
                a[j] |= num;
            }
        }
    }

    for (int num : a)
        std::cout << num << " ";

    std::cout << "\n";

    return 0;
}
