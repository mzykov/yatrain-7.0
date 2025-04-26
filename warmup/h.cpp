#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct TreeNode {
    int val = 0;
    std::shared_ptr<TreeNode> left  = nullptr;
    std::shared_ptr<TreeNode> right = nullptr;

    bool Add(int key) {
        if (this->val == key)
            return false;
        else {
            if (key > this->val) {
                if (this->right != nullptr)
                    return this->right->Add(key);
                else {
                    this->right = std::make_shared<TreeNode>(key);
                    return true;
                }
            } else {
                if (this->left != nullptr)
                    return this->left->Add(key);
                else {
                    this->left = std::make_shared<TreeNode>(key);
                    return true;
                }
            }
        }
    }
    bool Search(int key) {
        if (this->val == key)
            return true;
        else {
            if (key > this->val) {
                if (this->right != nullptr)
                    return this->right->Search(key);
                else
                    return false;
            } else {
                if (this->left != nullptr)
                    return this->left->Search(key);
                else
                    return false;
            }
        }
    }
};

void PrintTree(std::shared_ptr<TreeNode> node, int h) {
    if (node->left != nullptr)
        PrintTree(node->left, h + 1);

    std::string padding(h, '.');
    std::cout << padding << node->val << "\n";

    if (node->right != nullptr)
        PrintTree(node->right, h + 1);
}

int main() {
    std::shared_ptr<TreeNode> root = nullptr;
    std::string cmd;

    while (std::cin >> cmd) {
        if (cmd == "ADD") {
            int key;
            std::cin >> key;
            if (root) {
                if (root->Add(key))
                    std::cout << "DONE" << "\n";
                else
                    std::cout << "ALREADY" << "\n";
            } else {
                root = std::make_shared<TreeNode>(key);
                std::cout << "DONE" << "\n";
            }
        } else if (cmd == "SEARCH") {
            int key;
            std::cin >> key;
            if (root && root->Search(key))
                std::cout << "YES" << "\n";
            else
                std::cout << "NO" << "\n";
        } else if (cmd == "PRINTTREE") {
            PrintTree(root, 0);
        }
    }

    return 0;
}
