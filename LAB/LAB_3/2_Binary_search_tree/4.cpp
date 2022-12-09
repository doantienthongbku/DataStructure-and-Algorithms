#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

class BSTNode {
public:
    int val;
    BSTNode *left;
    BSTNode *right;
    BSTNode() {
        this->left = this->right = nullptr;
    }
    BSTNode(int val) {
        this->val = val;
        this->left = this->right = nullptr;
    }
    BSTNode(int val, BSTNode*& left, BSTNode*& right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

vector<int> levelAlterTraverse(BSTNode* root) {
}

int main() {
    int arr[] = {0, 3, 5, 1, 2, 4};
    BSTNode* root = BSTNode::createBSTree(arr, arr + sizeof(arr)/sizeof(int));
    printVector(levelAlterTraverse(root));
    BSTNode::deleteTree(root);

    return 0;
}