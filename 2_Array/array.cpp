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


int main() {


    return 0;
}