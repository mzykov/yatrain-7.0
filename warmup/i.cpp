#include <iostream>
#include <memory>
#include <vector>

struct TreeNode {
    int rank = 1;
    bool seen = false;
    std::vector<std::shared_ptr<TreeNode>> nodes;
};

void traverse_tree(std::shared_ptr<TreeNode> root) {
    root->seen = true;
    for (auto node : root->nodes) {
        if (node->seen)
            continue;
        traverse_tree(node);
        root->rank += node->rank;
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<std::shared_ptr<TreeNode>> v(n + 1, nullptr);

    while (--n) {
        int a, b;
        std::cin >> a >> b;

        if (v[a] == nullptr) {
            v[a] = std::make_shared<TreeNode>();
        }

        if (v[b] == nullptr) {
            v[b] = std::make_shared<TreeNode>();
        }

        v[a]->nodes.push_back(v[b]);
        v[b]->nodes.push_back(v[a]);
    }

    traverse_tree(v[1]);

    for (int i = 1; i < v.size(); ++i)
        std::cout << v[i]->rank << " ";

    std::cout << "\n";

    return 0;
}
