#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <format>

class Stack {
public:
    std::string push(int num) {
        v_.push_back(num);
        return "ok";
    }
    int pop() {
        int el = v_.back();
        v_.pop_back();
        return el;
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
    Stack s;

    while (true) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "push") {
            int num;
            std::cin >> num;
            std::cout << s.push(num) << "\n";
        }
        else if (cmd == "pop") {
            if (s.empty())
                std::cout << "error\n";
            else
                std::cout << s.pop() << "\n";
        }
        else if (cmd == "back") {
            if (s.empty())
                std::cout << "error\n";
            else
                std::cout << s.back() << "\n";
        }
        else if (cmd == "size") {
            std::cout << s.size() << "\n";
        }
        else if (cmd == "clear") {
            std::cout << s.clear() << "\n";
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
