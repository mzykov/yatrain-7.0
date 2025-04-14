#include <iostream>
#include <queue>
#include <string>
#include <vector>

std::vector<int> take_elem(std::priority_queue<std::vector<int>>& q, std::vector<bool>& used) {
    std::vector<int> res;

    while (!q.empty()) {
        auto el = q.top();
        if (used[el[2]]) {
            q.pop();
            continue;
        } else {
            q.pop();
            used[el[2]] = true;
            res = el;
            break;
        }
    }

    return res;
}

int main() {
    int n;
    std::cin >> n;

    std::priority_queue<std::vector<int>> zero, one;

    for (int i = 0; i < n; ++i) {
        std::string order;
        std::cin >> order;

        std::vector<int> p_odd(4, 0), p_even(4, 0);

        for (int j = 0; j < order.length(); ++j) {
            if ((j + 1) % 2) {
                if (order[j] == 'S')
                    ++p_odd[0];
                else
                    ++p_odd[1];
            } else {
                if (order[j] == 'S')
                    ++p_even[0];
                else
                    ++p_even[1];
            }
        }

        p_odd[2]  = i;
        p_odd[3]  = order.length();
        p_even[2] = i;
        p_even[3] = order.length();

        zero.push(p_odd);
        one.push(p_even);
    }

    std::vector<bool> used(n, false);
    int res = 0, len = 0;

    while (!zero.empty() && !one.empty()) {
        if (len % 2 == 0) {
            auto el = take_elem(zero, used);
            if (!el.empty()) {
                res += el[0];
                len += el[3];
            }
        } else {
            auto el = take_elem(one, used);
            if (!el.empty()) {
                res += el[0];
                len += el[3];
            }
        }
    }

    while (!zero.empty()) {
        auto el = take_elem(zero, used);
        if (!el.empty())
            res += el[0];
    }

    while (!one.empty()) {
        auto el = take_elem(one, used);
        if (!el.empty())
            res += el[0];
    }

    std::cout << res << "\n";

    return 0;
}
