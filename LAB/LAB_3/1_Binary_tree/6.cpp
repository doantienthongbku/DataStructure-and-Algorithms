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

int computeMaxLength(BTNode* root, int& maxLen) {
    if (root == NULL) return 0;
    int left = computeMaxLength(root->left, maxLen);
    int right = computeMaxLength(root->right, maxLen);
    maxLen = max(maxLen, left + right + 1);
    return max(left, right);
}

int longestPathSum(BTNode* root) {
    // returns the sum of the largest path from the root node to a leaf node
}

int main() {
    int arr[] = {-1,0,0,2,2,3,3,5};
    int value[] = {1,5,4,7,12,4,8,2};
    BTNode* root = BTNode::createTree(arr, arr + sizeof(arr)/sizeof(int), value);
    cout << longestPathSum(root);

    return 0;
}