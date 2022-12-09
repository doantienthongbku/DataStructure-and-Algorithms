#include <iostream>
#include <iomanip>
#include <functional>
using namespace std;

template <class T>
class Queue {
public:
    Queue();
    virtual ~Queue();
    Queue(const Queue<T> &);
    Queue(Queue<T> &&);

    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual Queue<T>& operator=(const Queue<T> &) = 0;
    virtual Queue<T>& operator=(Queue<T> &&) = 0;   // move assignment

    virtual void enqueue(const T &) = 0;
    virtual T dequeue(T&&) = 0;
    virtual T& dequeue() = 0;
    virtual T& first() = 0;
    virtual const T& getFirst() const = 0;
};

template <class T>
class L1Queue : public L1List<T>, public Queue<T> {
public:
    L1Queue() : L1List<T>() {}
    virtual ~L1Queue() { this->clear(); }
    L1Queue(const L1Queue<T> & q) : L1List<T>(q) {}
    L1Queue(L1Queue<T> && q) : L1List<T>(q) {}

    int size() const { return L1List<T>::size(); }
    bool isEmpty() const { return L1List<T>::isEmpty(); }
    void clear() { L1List<T>::clear(); }
    Queue<T>& operator=(const Queue<T> & q) { return *this; }
    Queue<T>& operator=(Queue<T> && q) { return *this; }

    void enqueue(const T & val) { L1List<T>::insert(val, L1List<T>::size); }
    void enqueue(T && val) { L1List<T>::insert(std::move(val), L1List<T>::size); }
    void dequeue() { L1List<T>::remove(0); }
    T& first() {
        if (!this->pHead) throw DSA_Exception(-10, "L1Queue:empty queue");
        return this->pHead->data;
    }
    const T& getFirst() const {
        if (!this->pHead) throw DSA_Exception(-10, "L1Queue:empty queue");
        return this->pHead->data;
    }
};

template <class T>
class BinarySearchTree {
protected:
    struct Node {
        T data;
        Node *pLeft, *pRight;
        Node(const T & val, Node * pL = nullptr, Node * pR = nullptr) : data(val), pLeft(pL), pRight(pR) {}
    };
    Node *pRoot;
    size_t nE;

    void clear(Node *pR) {if(pR) {
        clear(pR->pLeft);
        clear(pR->pRight);
        delete pR;
        nE = 0;
    }}
    void insert(const T & val, Node * & pR) {
        if(pR) {
            if(pR->data>val) insert(val, pR->pLeft);
            else insert(val, pR->pRight);
        }
        else { pR = new Node(val); nE++; }
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
    BinarySearchTree() : pRoot(nullptr), nE(0) {}
    virtual ~BinarySearchTree() {clear();}
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
    BinarySearchTree<int> *pBST = new BinarySearchTree<int>;
    int N = 10;
    for (int i = 0; i < N; i++) {
        int val = rand() % 100;
        pBST->insert(val);
        clog << setw(5) << val;
    }
    pBST->traverseNLR([](int & val) {std::cout << setw(5) << val;}); cout << endl;
    pBST->traverseBF([](int & val) {std::cout << setw(5) << val;}); cout << endl;
    int s = 0;
    pBST->traverseNLR([&s](int & val) {s += val;});
    cout << "Average val: " << (double)s / pBST->size() << endl;

    return 0;
}