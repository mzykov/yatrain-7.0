#include <array>
#include <iostream>
#include <list>

std::list<std::array<unsigned long, 2>>::iterator
bankruptFishFactory(std::list<std::array<unsigned long, 2>> &a, std::list<std::array<unsigned long, 2>>::iterator &it, unsigned long &total, bool is_first, bool is_last) {
    auto &av = *it;

    if (is_first) {
        auto &av_next = *std::next(it);
        total -= av[1];
        total -= av_next[1];
        av_next[0] += av[0];
        av_next[1] = av_next[0] * av_next[0];
        total += av_next[1];
        it = std::next(it);
        a.erase(std::prev(it));
    }
    else if (is_last) {
        auto &av_prev = *std::prev(it);
        total -= av[1];
        total -= av_prev[1];
        av_prev[0] += av[0];
        av_prev[1] = av_prev[0] * av_prev[0];
        total += av_prev[1];
        it = std::prev(it);
        a.erase(std::next(it));
        it = std::next(it);
    }
    else {
        auto &av_prev = *std::prev(it);
        auto &av_next = *std::next(it);

        unsigned long left_len  = av[0]/2;
        unsigned long right_len = av[0] - left_len;

        total -= av_next[1];
        total -= av[1];
        total -= av_prev[1];

        av_prev[0] += left_len;
        av_next[0] += right_len;

        av_prev[1] = av_prev[0] * av_prev[0];
        av_next[1] = av_next[0] * av_next[0];

        total += av_next[1];
        total += av_prev[1];

        it = std::prev(it);
        a.erase(std::next(it));
        it = std::next(it);
    }

    return it;
}

std::list<std::array<unsigned long, 2>>::iterator
divideFishFactory(std::list<std::array<unsigned long, 2>> &a, std::list<std::array<unsigned long, 2>>::iterator &it, unsigned long &total) {
    auto &av = *it;
    unsigned long left_len  = av[0]/2;
    unsigned long right_len = av[0] - left_len;

    std::array<unsigned long, 2> new_v {{ right_len, right_len * right_len }};

    total -= av[1];
    av[0] = left_len;
    av[1] = left_len * left_len;

    total += av[1];
    total += new_v[1];

    a.insert(std::next(it), std::move(new_v));

    return it;
}

int main() {
    int n;
    std::cin >> n;

    unsigned long total = 0;
    std::list<std::array<unsigned long, 2>> a;
    a.push_back({ 0, 0 });

    while (n--) {
        unsigned long v;
        std::cin >> v;
        auto v2 = v*v;
        a.push_back({ v, v2 });
        total += v2;
    }

    std::cout << total << "\n";

    int k;
    std::cin >> k;

    int prev_v = 0;
    auto it = a.begin();

    while (k--) {
        int e, v;
        std::cin >> e >> v;

        std::advance(it, v - prev_v);

        if (e == 1)
            it = bankruptFishFactory(a, it, total, v == 1, v == a.size() - 1);
        else if (e == 2)
            it = divideFishFactory(a, it, total);

        prev_v = v;
        std::cout << total << "\n";
    }

    return 0;
}
