#include <iostream>
using namespace std;

template<class T>
class List {
public:
    List() {}
    virtual ~List() {}
    virtual int size() const = 0;
    virtual isEmpty() const = 0;
    virtual void clear() = 0;
    virtual List<T>& operator=(const List<T> &) = 0;
    virtual List<T>& operator=(const List<T> &&) = 0; // mode assignment
    virtual void reverse() = 0;
    virtual void append(List<T> &) = 0;
    virtual List<T>* operator+(const List<T> &) = 0;
    virtual List<T>* split(int) = 0;    // create a new list from index, and trim the current list

    virtual void insert(const T&, int) = 0;
    virtual void insert(T&&, int) = 0;
    virtual void remove(int) = 0;
    virtual T* find(const T&) = 0;
    virtual T* find(const T& a, bool (*eq)(const T&, const t&)) = 0;
    virtual T* findAll(const T& a, List<T*> *pRetl) = 0;
    virtual T* findAll(const T& a, bool (*eq)(const T&, const t&), List<T*> *pRetl) = 0;
    virtual T& operator[](int) = 0;
};

template <class T>
class Queue : public List<T> {
public:
    Queue() {}
    virtual ~Queue() {}
    virtual void enqueue(const T&) = 0;
    virtual void enqueue(T&&) = 0;
    virtual T dequeue() = 0;
    virtual T& first() = 0;
    virtual T& last() = 0;
};

template <class T>
class L1Queue : public Queue<T> {
    struct Node {
        T data;
        Node *pNext;
        Node(const T& a) : data(a), pNext(nullptr) {}
        Node(T&& a) : data(a), pNext(nullptr) {}
    };
    Node *pHead, *pTail;
    int nE;
public:
    L1Queue() : pHead(nullptr), pTail(nullptr), nE(0) {}
    ~L1Queue() { clear(); }
    int size() const { return nE; }
    bool isEmpty() const { return nE == 0; }
    void clear() {
        while (pHead) {
            Node *p = pHead;
            pHead = pHead->pNext;
            delete p;
        }
        pTail = nullptr;
        nE = 0;
    }
    void enqueue(const T& a) {
        Node *p = new Node(a);
        if (pTail) pTail->pNext = p;
        else pHead = p;
        pTail = p;
        nE++;
    }
    void enqueue(T&& a) {
        Node *p = new Node(a);
        if (pTail) pTail->pNext = p;
        else pHead = p;
        pTail = p;
        nE++;
    }
    T dequeue() {
        if (!pHead) return T();
        Node *p = pHead;
        T ret = p->data;
        pHead = pHead->pNext;
        delete p;
        if (!pHead) pTail = nullptr;
        nE--;
        return ret;
    }
    T& first() { return pHead->data; }
    T& last() { return pTail->data; }
};

int main() {
    // test L1Queue
    L1Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    while (!q.isEmpty()) {
        cout << q.dequeue() << " ";
    }
    cout << endl;

    return 0;
}