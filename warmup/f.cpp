#include <algorithm>
#include <iostream>
#include <vector>

class Heap {
public:
    void Insert(int key) {
        keys_.push_back(key);
        siftUp(keys_.size() - 1);
    }
    int Extract() {
        int key = keys_[0];
        std::swap(keys_.front(), keys_.back());
        keys_.pop_back();
        siftDown(0);
        return key;
    }
    static bool IsInsertCmd(int cmd) {
        return cmd == 0;
    }
    static bool IsExtractCmd(int cmd) {
        return cmd == 1;
    }
private:
    int nary_ = 3;
    std::vector<int> keys_;

    inline bool cmp(int a, int b) {
        return a > b;
    }
    inline int parentIndex(int i) {
        return (i - 1) / nary_;
    }
    int childIndex(int i) {
        int last_index  = keys_.size() - 1;
        int first_child = i * nary_ + 1;

        if (first_child > last_index)
            return 0;

        int last_child  = std::min((i + 1) * nary_, last_index);
        int optimal_key = keys_[first_child];
        int res = first_child;

        while (++first_child <= last_child) {
            if (keys_[first_child] > optimal_key) {
                optimal_key = keys_[first_child];
                res = first_child;
            }
        }

        return res;
    }
    void siftDown(int i) {
        int c = childIndex(i);

        while (c > 0 && keys_[c] > keys_[i]) {
            std::swap(keys_[c], keys_[i]);
            i = c;
            c = childIndex(i);
        }
    }
    void siftUp(int i) {
        int p = parentIndex(i);

        while (i > 0 && keys_[p] < keys_[i]) {
            std::swap(keys_[p], keys_[i]);
            i = p;
            p = parentIndex(i);
        }
    }
};

int main() {
    int n;
    std::cin >> n;

    Heap heap;

    while (n--) {
        int cmd;
        std::cin >> cmd;

        if (Heap::IsInsertCmd(cmd)) {
            int key;
            std::cin >> key;
            heap.Insert(key);
        } else if (Heap::IsExtractCmd(cmd)) {
            std::cout << heap.Extract() << "\n";
        }
    }

    return 0;
}
