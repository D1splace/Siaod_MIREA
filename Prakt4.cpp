#include <iostream>
#include <iomanip>
using namespace std;
struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для копирования левых вершин в правые
TreeNode* copyLeftToRight(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }

    TreeNode* newRoot = new TreeNode(root->value);
    newRoot->right = copyLeftToRight(root->left);
    newRoot->left = copyLeftToRight(root->left);

    return newRoot;
}

// Функция для вывода дерева
void printTree(TreeNode* node, int indent = 0) {
    if (node) {
        if (node->right) {
            printTree(node->right, indent + 4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (node->right) cout << " /\n" << setw(indent) << ' ';
            cout << node->value << "\n ";
        if (node->left) {
            cout << setw(indent) << ' ' << " \\\n";
            printTree(node->left, indent + 4);
        }
    }
}

int main() {
    setlocale(0, "");
    // Создание исходного дерева
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);

    // Копирование левых вершин в правые
    TreeNode* newRoot = copyLeftToRight(root);

    // Вывод исходного дерева
    std::cout << "Исходное дерево:" << std::endl;
    printTree(root);

    // Вывод дерева после копирования
    std::cout << "Дерево после копирования:" << std::endl;
    printTree(newRoot);

    // Освобождение памяти
    delete root;
    delete newRoot;

    return 0;
}