#include <algorithm>
#include <iostream>
#include <vector>

int reduced_length(std::vector<int>& x) {
    sort(x.begin(), x.end());

    if (x.size() < 4) {
        return x.back() - x.front();
    }

    int f0 = x[1] - x[0];
    int f1 = x[2] - x[1] + f0;

    for (int i = 3; i < x.size(); ++i) {
        int f_next = x[i] - x[i-1] + std::min(f0, f1);
        f0 = f1;
        f1 = f_next;
    }

    return f1;
}

int main() {
    int n = 1;
    std::cin >> n;

    std::vector<int> x;

    while (n--) {
        int p;
        std::cin >> p;
        x.push_back(p);
    }

    std::cout << reduced_length(x) << "\n";

    return 0;
}
