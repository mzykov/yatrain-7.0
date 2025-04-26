#include <iostream>

int main() {
    unsigned long long x;
    std::cin >> x;
    short count = 0;
    for (; x > 0; x >>= 1) {
        if (x & 1)
            ++count;
    }
    std::cout << count << "\n";
    return 0;
}
