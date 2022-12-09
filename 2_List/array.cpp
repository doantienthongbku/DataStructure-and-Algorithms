#include <iostream>
using namespace std;

template<class T>
class List {
public:
    virtual List() {}
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

template<class T>
class L1List : public List<T> {
public:
    L1List() : pHead(nullptr), pTail(nullptr), _size(0) {}
    virtual ~L1List() { this->clear(); }
    L1List(const L1List<T> & l) : pHead(nullptr), pTail(nullptr), _size(0) {
        Node *p = l.pHead;
        while (p) {
            this->insert(p->data, this->_size);
            p = p->pNext;
        }
    }
    L1List(L1List<T> && l) : pHead(l.pHead), pTail(l.pTail), _size(l._size) {
        l.pHead = l.pTail = nullptr;
        l._size = 0;
    }

    int size() const { return this->_size; }
    bool isEmpty() const { return this->_size == 0; }
    void clear() {
        Node *p = this->pHead;
        while (p) {
            Node *q = p;
            p = p->pNext;
            delete q;
        }
        this->pHead = this->pTail = nullptr;
        this->_size = 0;
    }
    L1List<T>& operator=(const L1List<T> & l) {
        this->clear();
        Node *p = l.pHead;
        while (p) {
            this->insert(p->data, this->_size);
            p = p->pNext;
        }
        return *this;
    }
    L1List<T>& operator=(L1List<T> && l) {
        this->clear();
        this->pHead = l.pHead;
        this->pTail = l.pTail;
        this->_size = l._size;
        l.pHead = l.pTail = nullptr;
        l._size = 0;
        return *this;
    }

    void reverse() {
        if (this->_size <= 1) return;
        Node *p = this->pHead;
        Node *q = p->pNext;
        p->pNext = nullptr;
        while (q) {
            Node *r = q->pNext;
            q->pNext = p;
            p = q;
            q = r;
        }
        Node *t = this->pHead;
        this->pHead = this->pTail;
        this->pTail = t;
    }
    void append(L1List<T> & l) {
        if (l.isEmpty()) return;
        if (this->isEmpty()) {
            this->pHead = l.pHead;
            this->pTail = l.pTail;
            this->_size = l._size;
            l.pHead = l.pTail = nullptr;
            l._size = 0;
            return;
        }
        this->pTail->pNext = l.pHead;
        this->pTail = l.pTail;
        this->_size += l._size;
        l.pHead = l.pTail = nullptr;
        l._size = 0;
    }
    L1List<T>* operator+(const L1List<T> & l) {
        L1List<T> *pRet = new L1List<T>();
        pRet->append(*this);
        pRet->append(l);
        return pRet;
    }
    L1List<T>* split(int i) {
        if (i <= 0) return nullptr;
        if (i >= this->_size) return nullptr;
        L1List<T> *pRet = new L1List<T>();
        Node *p = this->pHead;
        while (i > 1) {
            p = p->pNext;
            --i;
        }
        pRet->pHead = p->pNext;
        pRet->pTail = this->pTail;
        pRet->_size = this->_size - i;
        this->pTail = p;
        this->pTail->pNext = nullptr;
        this->_size = i;
        return pRet;
    }

    void insert(const T& a, int i) {
        if (i < 0) return;
        if (i > this->_size) return;
        Node *p = new Node(a);
        if (i == 0) {
            p->pNext = this->pHead;
            this->pHead = p;
            if (this->_size == 0) this->pTail = p;
        } else if (i == this->_size) {
            this->pTail->pNext = p;
            this->pTail = p;
        } else {
            Node *q = this->pHead;
            while (i > 1) {
                q = q->pNext;
                --i;
            }
            p->pNext = q->pNext;
            q->pNext = p;
        }
        ++this->_size;
    }
    void insert(T&& a, int i) {
        if (i < 0) return;
        if (i > this->_size) return;
        Node *p = new Node(a);
        if (i == 0) {
            p->pNext = this->pHead;
            this->pHead = p;
            if (this->_size == 0) this->pTail = p;
        } else if (i == this->_size) {
            this->pTail->pNext = p;
            this->pTail = p;
        } else {
            Node *q = this->pHead;
            while (i > 1) {
                q = q->pNext;
                --i;
            }
            p->pNext = q->pNext;
            q->pNext = p;
        }
        ++this->_size;
    }


int main() {


    return 0;
}