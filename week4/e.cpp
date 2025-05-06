#include <array>
#include <iostream>
#include <queue>
#include <vector>

bool playElement(std::vector<std::array<int,4>> &v, int index, int round, std::queue<int> &leaved) {
    auto &curr = v[index];

    int prev_index = curr[1];
    int next_index = curr[2];

    if (prev_index == next_index)
        return false;

    if (curr[0] < v[prev_index][0] && curr[0] < v[next_index][0]) {
        curr[3] = round;
        leaved.push(index);
        return true;
    }

    return false;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::array<int,4>> v(n, {{0, 0, 0, 0}});

    for (int i = 0; i < n; ++i) {
        std::cin >> v[i][0];       // curr value
        v[i][1] = (i - 1 + n) % n; // prev index
        v[i][2] = (i + 1) % n;     // next index
        v[i][3] = 0;               // exit round
    }

    int round = 1;
    std::queue<int> leaved;

    for (int i = 0; i < n; ++i) {
        if (playElement(v, i, round, leaved) == true)
            ++i;
    }

    while (!leaved.empty()) {
        ++round;
        int sz = leaved.size();

        // repair links
        for (int i = 0; i < sz; ++i) {
            int leaved_index = leaved.front();
            leaved.pop();
            leaved.push(leaved_index);

            const auto &leaved_element = v[leaved_index];

            auto &prev = v[leaved_element[1]];
            auto &next = v[leaved_element[2]];

            next[1] = leaved_element[1];
            prev[2] = leaved_element[2];
        }

        // play next round
        for (int i = 0; i < sz; ++i) {
            int leaved_index = leaved.front();
            leaved.pop();
            const auto &leaved_element = v[leaved_index];

            int prev_index = leaved_element[1];
            playElement(v, prev_index, round, leaved);

            int next_index = leaved_element[2];
            playElement(v, next_index, round, leaved);
        }
    }

    for (int i = 0; i < n; ++i)
        std::cout << v[i][3] << " ";

    std::cout << "\n";

    return 0;
}
