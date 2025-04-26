#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

struct TreeNode {
    std::string val;
    std::vector<std::shared_ptr<TreeNode>> nodes;
};

std::vector<std::pair<std::string, int>> traverse_tree(const std::shared_ptr<TreeNode> root, int h) {
    if (root == nullptr)
        return {};

    std::vector<std::pair<std::string, int>> result { { root->val, h } };

    for (const auto node : root->nodes) {
        auto children = traverse_tree(node, h + 1);
        result.insert(result.end(), children.begin(), children.end());
    }

    return result;
}

int main() {
    int n;
    std::cin >> n;

    std::unordered_set<std::string> children;
    std::unordered_map<std::string, std::shared_ptr<TreeNode>> parents;

    while (--n) {
        std::string child_name, parent_name;
        std::cin >> child_name >> parent_name;

        children.insert(child_name);

        if (parents.count(parent_name) == 0) {
            parents[parent_name] = std::make_shared<TreeNode>(parent_name);
        }

        if (parents.count(child_name) == 0) {
            parents[child_name] = std::make_shared<TreeNode>(child_name);
        }

        parents[parent_name]->nodes.push_back(parents[child_name]);
    }

    std::shared_ptr<TreeNode> root = nullptr;

    for (const auto& [name, node] : parents) {
        if (children.count(name) == 0) {
            root = node;
            break;
        }
    }

    auto result = traverse_tree(root, 0);
    std::sort(result.begin(), result.end());

    for (const auto& [name, h] : result)
        std::cout << name << " " << h << "\n";

    return 0;
}
