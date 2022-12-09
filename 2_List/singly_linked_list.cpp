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



int main() {
    cout << "hello world" << endl;

    return 0;
}