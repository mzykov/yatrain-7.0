#include <algorithm>
#include <iostream>

unsigned short get_length(unsigned short n) {
    unsigned short len = 0;
    while (n) {
        ++len;
        n >>= 1;
    }
    return len;
}

unsigned short next_permutation(unsigned short n, unsigned short len) {
    return (((n << 1) & ((1 << (len)) - 1)) | ((n & (1 << (len - 1))) > 0 ? 1 : 0));
}

int main() {
    unsigned short n;
    std::cin >> n;

    unsigned short max_n = n, next_n = n;
    unsigned short len = get_length(n);

    for (unsigned short i = 0; i < len; ++i) {
        next_n = next_permutation(next_n, len);
        max_n = std::max(max_n, next_n);
    }

    std::cout << max_n << "\n";

    return 0;
}
