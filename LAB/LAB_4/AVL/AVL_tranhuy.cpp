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
class AVLTree
{
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

    void rotateLeft(Node *&root){
        Node *p = root->pRight;
        root->pRight = p->pLeft;
        p->pLeft = root;
        root = p;
    }

    void rotateRight(Node *&root){
        Node *p = root->pLeft;
        root->pLeft = p->pRight;
        p->pRight = root;
        root = p;
    }

    void balanceFromLeft(Node *&root){
        Node *p = root->pLeft;
        switch(p->balance){
        case LH:
            root->balance = EH;
            p->balance = EH;
            rotateRight(root);
            break;
        case EH:
            break;
        case RH:
            Node *w = p->pRight;
            switch(w->balance){
            case LH:
                root->balance = RH;
                p->balance = EH;
                break;
            case EH:
                root->balance = EH;
                p->balance = EH;
            case RH:
                root->balance = EH;
                p->balance = LH;
            }
            w->balance = EH;
            rotateLeft(p);
            root->pLeft = p;
            rotateRight(root);
        }
    }

    void balanceFromRight(Node *&root){
        Node *p = root->pRight;
        switch(p->balance){
        case LH:
            Node *w = p->pLeft;
            switch(w->balance){
            case LH:
                root->balance = EH;
                p->balance = RH;
                break;
            case EH:
                root->balance = EH;
                p->balance = EH;
            case RH:
                root->balance = LH;
                p->balance = EH;
            }
            w->balance = EH;
            rotateRight(p);
            root->pRight = p;
            rotateLeft(root);
            break;
        case EH:
            break;
        case RH:
            root->balance = EH;
            p->balance = EH;
            rotateLeft(root);
        }
    }


    void insertIntoAVL(Node *&root, Node *newNode, bool &isTaller){
        if(root == NULL){
            root = newNode;
            isTaller = true;
        } else if (root->data > newNode->data){
            insertIntoAVL(root->pLeft, newNode, isTaller);
            if(isTaller) {
                switch(root->balance){
                case LH:
                    balanceFromLeft(root);
                    isTaller = false;
                    break;
                case EH:
                    root->balance = LH;
                    isTaller = true;
                    break;
                case RH:
                    root->balance = EH;
                    isTaller = false;
                }
            }
        } else {
            insertIntoAVL(root->pRight, newNode, isTaller);
            if(isTaller){
                switch(root->balance){
                case LH:
                    root->balance = EH;
                    isTaller = false;
                    break;
                case EH:
                    root->balance = RH;
                    isTaller = true;
                    break;
                case RH:
                    balanceFromRight(root);
                    isTaller = false;
                }
            }
        }
    }

    void insert(const T &value)
    {
        bool isTaller = false;
        Node* newNode = new Node(value);
        insertIntoAVL(root, newNode, isTaller);
    }

    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}posite! Reverse Psychology, eh?

We will be working only with strings (or character arrays in C) in this article.

I’ll be using a very simple hash function, that simpl
    };
};

int main(){
    AVLTree<int> avl;
    for (int i = 0; i < 9; i++){
        avl.insert(i);
    }
    avl.printTreeStructure();
}