#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    Node* addRec(T value, Node* node) {
        if (!node) return new Node(value);
        if (value <= node->value) node->pLeft = addRec(value, node->pLeft);
        else node->pRight = addRec(value, node->pRight);
        return node;
    }

    void add(T value){
        root = addRec(value, root);
    }
    
    Node* deleteNodeRec(Node* root, int key) {
        if (!root) return NULL;

        if (key < root->value) root->pLeft = deleteNodeRec(root->pLeft, key);
        else if (key > root->value) root->pRight = deleteNodeRec(root->pRight, key);
        else {
            if (!root->pLeft && !root->pRight) {
                return NULL;
            }
            else if (!root->pLeft || !root->pRight) {
                return root->pLeft ? root->pLeft : root->pRight;
            }
            else {                                          // case 3: 2 child node
                Node* p = root->pRight;
                while (p->pLeft) p = p->pLeft;
                root->value = p->value;
                root->pRight = deleteNodeRec(root->pRight, root->value);
            }
        }

        return root;
    }

    void deleteNode(T value){
        root = deleteNodeRec(root, value);
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

    T getMin() {
        Node* p = root;
        while (p->pLeft) p = p->pLeft;
        return p->value;
    }

    T getMax() {
        Node *p = root;
        while (p->pRight) p = p->pRight;
        return p->value;
    }

    bool findRec(Node* root, T i) {
        if (!root) return false;
        if (i < root->value) return findRec(root->pLeft, i);
        else if (i > root->value) return findRec(root->pRight, i);
        else return true;
    }
    
    bool find(T i) {
        return findRec(root, i);
    }

    T sumRec(Node* root, T l, T r) {
        if (!root) return 0;
        if (l > root->value) return sumRec(root->pRight, l, r);
        else if (r < root->value) return sumRec(root->pLeft, l, r);
        else return root->value + sumRec(root->pLeft, l, r) + sumRec(root->pRight, l, r);
    }

    T sum(T l, T r) {
        return sumRec(root, l, r);
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
	
    int values[] = { 32,0,2,84,34,78,70,60,95,71,26,62,0,22,95 };
    BinarySearchTree<int> bst;
    for (int i = 0; i < 15; ++i) {
        bst.add(values[i]);
    }

    cout << bst.find(34) << endl;
    cout << bst.sum(10, 40);

    return 0;
}