#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <format>

class Deque {
public:
    std::string push_front(int num) {
        v_.insert(v_.begin(), num);
        return "ok";
    }
    std::string push_back(int num) {
        v_.push_back(num);
        return "ok";
    }
    int pop_front() {
        int el = v_.front();
        v_.erase(v_.begin());
        return el;
    }
    int pop_back() {
        int el = v_.back();
        v_.pop_back();
        return el;
    }
    int front() {
        return v_.front();
    }
    int back() {
        return v_.back();
    }
    std::size_t size() {
        return v_.size();
    }
    std::string clear() {
        v_.clear();
        return "ok";
    }
    bool empty() {
        return v_.empty();
    }
private:
    std::vector<int> v_;
};

int main() {
    Deque q;

    while (true) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "push_front") {
            int num;
            std::cin >> num;
            std::cout << q.push_front(num) << "\n";
        }
        else if (cmd == "push_back") {
            int num;
            std::cin >> num;
            std::cout << q.push_back(num) << "\n";
        }
        else if (cmd == "pop_front") {
            if (q.empty())
                std::cout << "error\n";
            else
                std::cout << q.pop_front() << "\n";
        }
        else if (cmd == "pop_back") {
            if (q.empty())
                std::cout << "error\n";
            else
                std::cout << q.pop_back() << "\n";
        }
        else if (cmd == "front") {
            if (q.empty())
                std::cout << "error\n";
            else
                std::cout << q.front() << "\n";
        }
        else if (cmd == "back") {
            if (q.empty())
                std::cout << "error\n";
            else
                std::cout << q.back() << "\n";
        }
        else if (cmd == "size") {
            std::cout << q.size() << "\n";
        }
        else if (cmd == "clear") {
            std::cout << q.clear() << "\n";
        }
        else if (cmd == "exit") {
            std::cout << "bye\n";
            break;
        }
        else {
            throw std::logic_error{ std::format("Unknown command {}", cmd) };
        }
    }
    return 0;
}
