#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#define SEPARATOR "#<ab@17943918#@>#"

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

    //Helping function
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

    void deleteNodeRec(T value, Node* node) {
        if (!node) return;

        if (node->value > value) deleteNodeRec(value, node->pLeft);
        else if (node->value < value) deleteNodeRec(value, node->pRight);
        else {
            if (node->pLeft && node->pRight) {
                Node *p = node->pRight;
                while (p && p->pLeft) p = p->pLeft;
                node->value = p->value;
                deleteNodeRec(p->value, node->pRight);
            } else if (node->pLeft) {
                Node *p = node;
                node = node->pLeft;
                delete p;
                p = nullptr;
            } else if (node->pRight) {
                Node *p = node;
                node = node->pRight;
                delete p;
                p = nullptr;
            } else {
                delete node;
                node = nullptr;
            }
        }
    }

    void deleteNode(T value){
        deleteNodeRec(value, this->root);
    }

    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder(){
        return inOrderRec(this->root);
    }

    class Node {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

int main() {
    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    cout << bst.inOrder();
    cout << endl;
    bst.deleteNode(9);
    cout << bst.inOrder();
    cout << endl;

    return 0;
}