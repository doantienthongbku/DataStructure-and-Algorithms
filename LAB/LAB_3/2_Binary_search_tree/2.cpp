#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class BinarySearchTree {
public:
    class Node;

private:
    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}
    //~BinarySearchTree() {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    //}

    class Node {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addRec(T value, Node* node) {
        if (node) {
            if (value <= node->value) {
                if (node->pLeft == nullptr) {
                    node->pLeft = new Node(value);
                } else {
                    addRec(value, node->pLeft);
                }
            } else {
                if (node->pRight == nullptr) {
                    node->pRight = new Node(value);
                } else {
                    addRec(value, node->pRight);
                }
            }
        } else {
            root = new Node(value);
        }
    }

    void add(T value){
        addRec(value, this->root);
    }
    // STUDENT ANSWER BEGIN
    // You can define other functions here to help you.
    T getMin() {
        //TODO: return the minimum values of nodes in the tree.
        Node *p = this->root;
        while (p && p->pLeft) p = p->pLeft;
        return p->value;
    }

    T getMax() {
        //TODO: return the maximum values of nodes in the tree.
        Node *p = this->root;
        while (p && p->pRight) p = p->pRight;
        return p->value;
    }
    // STUDENT ANSWER END
};

int main() {
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i) {
        bst.add(i);
    }
    cout << bst.getMin() << endl;
    cout << bst.getMax() << endl;

    return 0;
}