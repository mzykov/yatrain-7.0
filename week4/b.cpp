#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <format>

class Queue {
public:
    std::string push(int num) {
        v_.insert(v_.begin(), num);
        return "ok";
    }
    int pop() {
        int el = v_.back();
        v_.pop_back();
        return el;
    }
    int front() {
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
    Queue q;

    while (true) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "push") {
            int num;
            std::cin >> num;
            std::cout << q.push(num) << "\n";
        }
        else if (cmd == "pop") {
            if (q.empty())
                std::cout << "error\n";
            else
                std::cout << q.pop() << "\n";
        }
        else if (cmd == "front") {
            if (q.empty())
                std::cout << "error\n";
            else
                std::cout << q.front() << "\n";
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
