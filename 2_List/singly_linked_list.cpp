#include <iostream>
using namespace std;


template<class T>
class List {
public:
    struct forwardIterator {
        forwardIterator() {}
        forwardIterator(const forwardIterator & i) {}
        forwardIterator(const forwardInterator && i) {}
        virtual ~forwardIterator() {}
        virtual forwardIterator& operator=(const forwardIterator & i) {return *this;}
        virtual forwardIterator& operator=(const forwardIterator && i) {return *this;}
        virtual forwardIterator& operator+(unsigned int i) {return *this;}
        virtual forwardIterator& operator++() {return *this;}
        virtual forwardIterator& operator++(int) {return *this;}
        virtual T& operator*() { throw DSA_Exception(-100, "forwardIterator: operator* - Unused method"); }
        virtual bool operator==(const forwardIterator & i) const { return true; }
        virtual bool operator!=(const forwardIterator & i) const { return false; }
    };

    virtual forwardIterator begin() = 0;
    virtual forwardIterator end() = 0;

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
    virtual const T& at(int) = 0;
    virtual void traverse(std::function<void (T&)> op) = 0;
    virtual void traverse(std::function<void (T&&)> op) = 0;
    virtual void swapEle(int, int) = 0;
};

// implementation of the singly Linked List
template<class T>
class L1List: List<T> {
protected:
    struct Node {
        T       data;
        Node    *pNext;
        Node(const T &a, Node *pN = nullptr) : data(a), pNext(pN) {}
        Node(T && a, Node *pN = nullptr) : data(a), pNext(pN) {}
        Node() : pNext(nullptr) {}
    };

    Node    *pHead;
    int     nE; //optional

public:
    L1List() : pHead(nullptr), nE(0) {}
    L1List(const List<T> &aList) : pHead(nullptr), nE(0) {
        Node **pp = &pHead;
        aList.traverse([&pp](T & a) {
            *pp = new Node(a, *pp);
            pp = &(*pp)->pNext;
        });
    }
    L1List(List<T> && aList) : pHead(nullptr), nE(aList.size()){
        Node **pp = &pHead;
        aList.traverse([&pp](T & a) {
            *pp = new Node(a, *pp);
            pp = &(*pp)->pNext;
        });
    }

    ~L1List() {this->clear();}

    int size() const {  // const: cannot modify this, and can called by const feature
        return nE;
    }

    bool isEmpty() const { return !nE;}
    void clear() {
        while (pHead) {
            Node *p = pHead;
            pHead = pHead->pNext;
            delete p;
        };
    }
    List<T>& operator=(const List<T> & aList) {
        this->clear();
        nE = aList.size();
        Node **pp = &pHead;
        aList.traverse([&pp](T & a) {
            *pp = new Node(a, *pp);
            pp = &(*pp)->pNext;
        })
        return *this;
    }

    List<T>& operator=(const List<T> && aList) {
        this->clear();
        nE = aList.size();
        Node **pp = &pHead;
        aList.traverse([&pp](T & a) {
            *pp = new Node(std::move(a), *pp);
            pp = &(*pp)->pNext;
        })
        return *this;
    }

    void reverse() {
        Node *pNL = nullptr;
        while (pHead) {
            Node *p = pHead;
            pHead = pHead->pNext;
            p->pNext = pNL;
            pNL = p;
        }
        pHead = pNL;
    }
    void append(List<T> & aList) {
        Node **p = &pHead;
        while (*pp) pp = &(*pp)->pNext;
        int *pNE = &nE;
        aList.traverse([*pp, &pNE](T &a) { *pp = new Node(a); pp = &(*pp)->pNext; (*pNE)++; });
    }

    List<T>* operator+(const List<T> &) {

    }

    List<T>* split(int) {   // create a new list from index, and trim the current list
        if (idx < 0 || idx >= nE) return;
        int newNE = nE - idx;;
        Node **pp = &pHead;
        while (*pp && idx) {
            pp = &(*pp)->pNext;
            idx--;
            nE--;
        }
        List<T> pNL; = new L1List<T>;
        pNL->pHead = *pp;
        pNL->nE = newNE;
        *pp = nullptr;

        return pNL;
    }


    void insert(const T& a, int idx) {s
        Node **pp = &pHead;
        while (idx && *pp) {
            pp = &(*pp)->pNext;
            idx--;
        }
        *pp = new Node(a, *pp);
        nE++;
    }

    void insert(T&& a, int idx) {
        Node **pp = &pHead;
        while (idx && *pp) {
            pp = &(*pp)->pNext;
            idx--;
        }
        *pp = new Node(std::move(a), *pp);
        nE++;
    }

    void remove (int idx) {
        if (idx < 0 || idx >= nE) return;
        Node **pp = &pHead;
        while (idx && *pp) {
            pp = &(*pp)->pNext;
            idx--;
        }
        if (*pp) {
            Node *p = *pp;
            *pp = (*pp)->pNext;
            delete  p;
        }
        nE--;
    }
    T* find(const T& key) {
        Node *p = pHead;
        while (p) {
            if (p->data==key) return p;
        }
        // ...
    }
    T* find(const t& key, const (*eq))(const  T&, const T&) {

    }
    T* findAll(const T& key, List<T*> *pRetL) {

    }
    T& operator[](int idx) {
        if (idx < 0 || idx >= nE) throw DSA_Exception("L1List: Invalid index");
        Node *p = pHead;
        while (p && idx) {
            p = p->pNext;
            idx--;
        }
        return p->data;
    }

    const T& at(int idx) const {
        return this->operator[](idx);
    }
    void traverse(void (*op)(T&)) {
        for (T *p = pD, *pE = pD + nE; p ! pE) op(*p++);
    }
    void traverse(void (*op)(T&&)) {
        for (T *p = pD, *pE = pD + nE; p ! pE; p++) op(std::move(*p));
    }
    void swapEle(int lIdx, int rIdx) {

    }
};


int main() {
    cout << "hello world" << endl;

    return 0;
}