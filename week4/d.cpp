#include <algorithm>
#include <iostream>
#include <deque>
#include <string>

int main() {
    std::string num;
    std::getline(std::cin, num);

    int n = std::stoi(num);
    std::deque<std::string> v;

    while (!std::cin.eof() && n--) {
        std::string l;
        std::getline(std::cin, l);

        if (std::cin.eof())
            break;

        std::string prog;

        if (l.starts_with("Run ")) {
            prog = l.substr(4);
            v.push_back(prog);
        } else if (v.size() > 1) {
            int plus = std::count(l.begin(), l.end(), '+') % v.size();
            for (int j = 0; j < plus; ++j) {
                auto el = v.back();
                v.push_front(el);
                v.pop_back();
            }
            auto prog = v.back();
            v.pop_back();
            for (int j = 0; j < plus; ++j) {
                auto el = v.front();
                v.push_back(el);
                v.pop_front();
            }
            v.push_back(prog);
        }
        std::cout << v.back() << "\n";
    }

    return 0;
}
