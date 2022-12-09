#include <iostream>
#include <stack>
#include <queue>
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

void sumDigit(BTNode* subRoot, int* sum, int curSum) {
    curSum = (curSum * 10 + subRoot->val) % 27022001;
    if (subRoot->left == NULL && subRoot->right == NULL) {
        *sum = *sum + curSum;
        *sum = *sum % 27022001;
    }
    if (subRoot->left) sumDigit(subRoot->left, sum, curSum);
    if (subRoot->right) sumDigit(subRoot->right, sum, curSum);
}

int sumDigitPath(BTNode* root) {
    if (root == NULL) return 0;
    int sum = 0;
    sumDigit(root, &sum, 0);
    return sum;
}

int main() {
    int arr[] = {-1,0,0,2,2};
    int value[] = {3,5,2,1,4};
    BTNode* root = BTNode::createTree(arr, arr + sizeof(arr)/sizeof(int), value);
    cout << sumDigitPath(root);

    return 0;
}