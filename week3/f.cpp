#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;

    std::vector<unsigned int> rookx(n, 0), rooky(n, 0), rookz(n, 0);

    for (int i = 0; i < k; ++i) {
        int x, y, z;
        std::cin >> x >> y >> z;
        rookx[x] = 1;
        rooky[y] = 1;
        rookz[z] = 1;
    }

    return 0;
}
