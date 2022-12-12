#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue {
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n) {
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n) {
    cout << n << " ";
}

template<class T>
class AVLTree {
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node) {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight() { return this->getHeightRec(this->root); }
    void printTreeStructure() {
        int height = this->getHeight();
        if (this->root == NULL) {
            cout << "NULL\n";
            return;
        }

        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty()) {
            temp = q.front();
            q.pop();
            if (temp == NULL) {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode) {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    Node* rotL(Node* root) {
        Node* tmp = root->pRight;
        root->pRight = tmp->pLeft;
        tmp->pLeft = root;
        return tmp;
    }

    Node* rotR(Node* root) {
        Node* tmp = root->pLeft;
        root->pLeft = tmp->pRight;
        tmp->pRight = root;
        return tmp;
    }

    Node BalanceLeft(Node*& root, bool& taller) {
        Node* left = root->pLeft;
        if (left->balance == LH) {
            root = rotR(root);
            root->balance = EH;
            root->pRight->balance = EH;
            taller = false;
        }
        else if (left->balance == RH) {
            Node* right = left->pRight;
            if (!right) return root;
            if (right->balance == LH) {
                root->balance = RH;
                left->balance = EH;
            }
            else if (right->balance == EH) {
                root->balance = EH;
                left->balance = EH;
            }
            else {
                root->balance = EH;
                left->balance = LH;
            }
            right->balance = EH;
            root->pLeft = rotL(left);
            root = rotR(root);
            taller = false;
        }
        else {
            root = rotR(root);
            root->balance = RH;
            root->pRight->balance = LH;
            taller = false;
        }

        return root;
    }

    class Node {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main() {
    // AVLTree<int> avl;
    // for (int i = 0; i < 9; i++){
    //     avl.insert(i);
    // }
    // avl.printTreeStructure();

    return 0;
}