#include <iostream>
#include <iomanip>
#include <functional>
using namespace std;

template <class T>
class AVLTree {
protected:
    enum BFactor { EH = 0, LH, RH};
    struct Node {
        T data;
        Node *pLeft, *pRight;
        BFactor b;
        Node(const T & val, BFactor _b = EH, Node *pL = nullptr, Node *pR = nullptr) : data(val), b(_b), pLeft(pL), pRight(pR) {}
    };
    Node *pRoot;
    size_t nE;

    void clear(Node *pR) {
        if(pR) {
            clear(pR->pLeft);
            clear(pR->pRight);
            delete pR;
            nE = 0;
        }
    }
    void rotR(Node * & pR) {
        Node * p = pR->pLeft;
        pR->pLeft = p->pRight;
        p->pRight = pR;
        pR = p;
    }
    void rotL(Node * & pR) {
        Node * p = pR->pRight;
        pR->pRight = p->pLeft;
        p->pLeft = pR;
        pR = p;
    }

    // TODO: implement func balanced_left and balanced_right

    bool insert(const T & val, Node * & pR) {
        if(pR) {
            if(pR->data > val) {
                if (insert(val, pR->pLeft)) {
                    if (pR->b == EH) { pR->b = LH; return true; }
                    else if (pR->b == RH) { pR->b = EH; return false; }
                    if (pR->b  == EH) { // pR->b == LH
                        rotR(pR); pR->b = RH; pR->pRight->b = LH; return true;
                    }
                    else if (pR->b == LH) {
                        rotR(pR); pR->b = pR->pRight->b = EH; return false;
                    }
                    else {  // pR->b == RH
                        rotL(pR->pLeft); rotR(pR);
                        if (pR->b == EH) { pR->pLeft->b = pR->pRight->b = EH; }
                        else if (pR->b == LH) { pR->pLeft->b = EH; pR->pRight->b = RH; }
                        else { pR->pLeft->b = LH; pR->pRight->b = EH; } // pR->b == RH
                        return false;
                    }
                }
            }
            else {
                if (insert(val, pR->pRight)) {
                    if (pR->b == EH) { pR->b = RH; return true; }
                    else if (pR->b == LH) { pR->b = EH; return false; }
                    if (pR->b  == EH) { // pR->b == RH
                        rotL(pR); pR->b = LH; pR->pLeft->b = RH; return true;
                    }
                    else if (pR->b == RH) {
                        rotL(pR); pR->b = pR->pLeft->b = EH; return false;
                    }
                    else {  // pR->b == LH
                        rotR(pR->pRight); rotL(pR);
                        if (pR->b == EH) { pR->pLeft->b = pR->pRight->b = EH; }
                        else if (pR->b == LH) { pR->pLeft->b = EH; pR->pRight->b = RH; }
                        else { pR->pLeft->b = LH; pR->pRight->b = EH; } // pR->b == RH
                        return false;
                    }
                }
                return false;
            }
        }
        else { pR = new Node(val); nE++; return true; }
    }
    void remove(const T& key, Node * & pR) {
        if(!pR) return;
        if(pR->data > key) remove(key, pR->pLeft);
        else if(pR->data < key) remove(key, pR->pRight);
        if(pR->pLeft && pR->pRight) {
            Node * p = pR->pRight;
            while (p->pLeft) p = p->pLeft;
            pR->data = p->data;
            remove(p->data, pR->pRight);
        }
        else if (pR->pLeft){
            Node *p = pR;
            pR = pR->pLeft;
            delete p;
            nE--;
        }
        else if (pR->pRight) {
            Node * p = pR;
            pR = pR->pRight;
            delete p;
            nE--;
        }
        else {
            delete pR;
            pR = nullptr;
            nE--;
        }
    }
    T * find(const T & key, Node * pR) {
        if(!pR) return nullptr;
        if(pR->data == key) return &pR->data;
        if(pR->data>key) return find(key, pR->pLeft);
        else return find(key, pR->pRight);
    }
    void traverseNLR(Node * pR, std::function<void (T&)> op) { // pre-order
        if (pR) { op(pR->data); traverseNLR(pR->pLeft, op); traverseNLR(pR->pRight, op); }
    }
    // TODO: implement all order of tree
public:
    AVLTree() : pRoot(nullptr), nE(0) {}
    virtual ~AVLTree() {clear();}
    size_t size() const { return nE; }
    void clear() { clear(pRoot); pRoot = nullptr; nE = 0; }
    void insert(const T & val) { insert(val, pRoot); }
    void remove(const T & key) {remove(key, pRoot);}
    T* find(const T & key) {return find(key,pRoot);}
    T* findIter(const T & key) {
        for (Node *p = pRoot; p;) {
            if (p->data == key) return &p->data;
            else (p->data > key) ? p = p->pLeft : p = p->pRight;
        }
        return nullptr;
    }
    void traverseNLR(std::function<void (T&)> op) { traverseNLR(pRoot, op); }
    // TODO: implement all order of tree

    void traverseBF(std::function<void (T&)> op) {
        if (!pRoot) return;
        L1Queue<Node*> q;
        q.enqueue(pRoot);
        while (!q.isEmpty()) {
            Node *p = q.first();
            op(p->data);
            if (p->pLeft) q.enqueue(p->pLeft);
            if (p->pRight) q.enqueue(p->pRight);
            q.dequeue();
        }
    }

};


int main() {
    AVLTree<int> *pT = new AVLTree<int>;
    int N = 10;

    for (int i = 0; i < N; i++) {
        int val = rand() % 100;
        pT->insert(val);
        clog << setw(5) << val;
    }
}
