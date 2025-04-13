#include <algorithm>
#include <iostream>
#include <vector>

class Heap {
public:
    void Insert(int k) {
    
    }
    static bool IsInsertCmd(int cmd) const { return cmd == 0; }

    int Extract() {
        int res = data_[0];
        
        return res;
    }
    static bool IsExtractCmd(int cmd) const { return cmd == 1; }
private:
    std::vector<int> data_;
};

int main() {
    int n;
    std::cin >> n;

    Heap heap;

    while (n--) {
        int cmd;
        std::cin >> cmd;

        if (Heap::IsInsertCmd(cmd)) {
            int val;
            std::cin >> val;
            heap.Insert(val);
        } else if (Heap::IsExtractCmd(cmd)) {
            std::cout << heap.Extract() << "\n";
        } else {
            throw "Unknown command\n";
        }
    }

    return 0;
}
