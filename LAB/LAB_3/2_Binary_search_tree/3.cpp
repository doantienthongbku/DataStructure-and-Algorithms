#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<class T>
class BinarySearchTree
{
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

    bool findRec(T i, Node* node) {
        if (!node) return false;
        if (node->value > i) return findRec(i, node->pLeft);
        else if (node->value < i) return findRec(i, node->pRight);
        else return true;
    }

    bool find(T i) {
        // TODO: return true if value i is in the tree; otherwise, return false.
        return findRec(i, this->root);
    }

    T sumRec(T l, T r, Node* node) {
        if (!node) return 0;
        if (l > node->value) return sumRec(l, r, node->pRight);
        else if (r < node->value) return sumRec(l, r, node->pLeft);
        else return node->value + sumRec(l, r, node->pRight) + sumRec(l, r, node->pLeft);
    }

    T sum(T l, T r) {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        return sumRec(l, r, this->root);
    }
    // STUDENT ANSWER END
};

int main() {
    int values[] = { 34,81,73,48,66,91,19,84,78,79 };
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i) {
        bst.add(values[i]);
    }

    cout << bst.find(5) << endl;
    cout << bst.sum(10, 40);
    cout << endl;

    return 0;
}