#include <algorithm>
#include <iostream>
#include <array>

constexpr std::array<std::array<int,4>,4> m = {{
    { 0, 1, 2, 3 },
    { 1, 0, 3, 2 },
    { 2, 3, 0, 1 },
    { 3, 2, 1, 0 },
}};

int find_c(int x, int y) {
    if (x == y) {
        return 0;
    } else {
        int x_start = (x >> 2) << 2;
        int y_start = (y >> 2) << 2;
        int v_start = x_start == y_start ? 0 : x_start + y_start;
        return v_start + m[y % 4][x % 4];
    }
}

int find_y(int x, int c) {
    if (c == 0) {
        return x;
    } else if (c < 4) {
        int x_start = (x >> 2) << 2;
        int y_start = x_start, y_tail = 0;
        for (; y_tail < m.size(); ++y_tail)
            if (m[y_tail][x % 4] == c)
                break;
        return y_start + y_tail;
    } else {
        int x_start = (x >> 2) << 2;
        int y_start = 0, y_tail = 0;
        for (; y_tail < m.size(); ++y_tail) {
            y_start = c - x_start - m[y_tail][x % 4];
            if (find_c(x, y_start + y_tail) == c)
                break;
        }
        return y_start + y_tail;
    }
}

int main() {
    {
        int x, y;
        std::cin >> x >> y;
        std::cout << find_c(x, y) << "\n";
    }
    {
        int x, c;
        std::cin >> x >> c;
        std::cout << find_y(x, c) << "\n";
    }

    return 0;
}
