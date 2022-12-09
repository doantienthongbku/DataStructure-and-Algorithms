#include <iostream>
using namespace std;

class BTNode {
public:
    int val;
    BTNode *left;
    BTNode *right;
    BTNode() {
        this->left = this->right = NULL;
    }
    BTNode(int val) {
        this->val = val;
        this->left = this->right = NULL;
    }
    BTNode(int val, BTNode*& left, BTNode*& right) {
        this->val = val;
        this->left = left;
        this->right = right;
    }
};

int lowestAncestor(BTNode* root, int a, int b) {
    // returns the lowest ancestor node's val of node a and node b in this binary tree

}

int main() {
    int arr[] = {-1,0,0,2,2,3,3};
    BTNode* root = BTNode::createTree(arr, arr + sizeof(arr) / sizeof(int), NULL);
    cout << lowestAncestor(root, 4, 5);

    return 0;
}