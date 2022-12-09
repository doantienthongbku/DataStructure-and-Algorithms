#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template<class T>
class AVLTree {
public:
    class Node;
private:
    Node *root;
protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree(){}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
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
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
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

    // helper function
    int BL(Node* root) {
        if (root == NULL)
            return 0;
        return getHeightRec(root->pLeft) - getHeightRec(root->pRight);
    }

    Node* Rot_R(Node* root) {
        Node* old_root = root;
        Node* new_root = root->pLeft;
        old_root->pLeft = new_root->pRight;
        new_root->pRight = old_root;
        return new_root;
    }
    Node* Rot_L(Node* root) {
        Node* old_root = root;
        Node* new_root = root->pRight;
        old_root->pRight = new_root->pLeft;
        new_root->pLeft = old_root;
        return new_root;
    }
        
    Node* reBalance(Node* root) {
        int balance = BL(root);
        if (balance > 1) {
            int bll = BL(root->pLeft);
            if (bll > 0) {
                return Rot_R(root);
            } else {
                root->pLeft = Rot_L(root->pLeft);
                return Rot_R(root);
            }
        } else if (balance < -1) {
            int blr = BL(root->pRight);
            if (blr < 0) {
                return Rot_L(root);
            } else {
                root->pRight = Rot_R(root->pRight);
                return Rot_L(root);
            }
        }

        return root;
    }

    Node* insert(Node* root, T value) {
        if (root == NULL) {
            root = new Node(value);
            return root;
        }
        if (value >= root->data) {
            root->pRight = insert(root->pRight, value);
        } else {
            root->pLeft = insert(root->pLeft, value);
        }
        return reBalance(root);
    }


    void insert(const T &value) {
        this->root = insert(this->root, value);
    }

    // REMOVE

    //Helping functions
    Node* removeRec(Node *root, const T &value) {
        if (!root) return NULL;
        if (root->data > value) root->pLeft = removeRec(root->pLeft, value);
        else if (root->data < value) root->pRight = removeRec(root->pRight, value);
        else {
            if (root->pLeft && root->pRight) {
                Node *p = root->pRight;
                while (p->pLeft) p = p->pLeft;
                root->data = p->data;
                root = removeRec(root->pRight, p->data);
            }
            else if (root->pLeft){
                Node *p = root;
                root = root->pLeft;
                delete p;
            }
            else if (root->pRight) {
                Node * p = root;
                root = root->pRight;
                delete p;
            }
            else {
                delete root;
                root = nullptr;
                return NULL;
            }
        }

        return reBalance(root);
    }

    void remove(const T &value){
        root = removeRec(root, value);
    }

    void printInorderRec(Node* node) {
        if (node) {
            printInorderRec(node->pLeft);
            cout << node->data << " ";
            printInorderRec(node->pRight);
        }
    }

    void printInorder() {
        printInorderRec(root);
    }


    bool searchRec(Node* p, const T &value) {
        if (!p) return false;
        if (p->data == value) return true;
        else if (p->data > value) return searchRec(p->pLeft, value);
        else return searchRec(p->pRight, value);
    }

    bool search(const T &value) {
        return searchRec(root, value);
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
    AVLTree<int> avl;
    int arr[] = {10,52,98,32,68,92,40,13,42,63,99,100};
    for (int i = 0; i < 12; i++){
        avl.insert(arr[i]);
    }
    avl.printInorder();
    cout << endl;
    cout << avl.search(10);
    cout << endl;
}