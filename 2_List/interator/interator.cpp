#include <iostream>
#include "array_base.h"
using namespace std;

//  template for base iterator.
template <class T>
struct fwInterBase {
    fwInterBase() {}
    virtual ~fwInterBase() {}
    
    virtual fwInterBase<T>* clone() { return new fwInterBase<T>(*this); }
    virtual void operator+(unsigned int di) { }
    virtual void operator++() { }       // prefix
    virtual void operator++(int) { }    // postfix
    virtual T& operator*() { throw std::DSA_Exception(-100, "fwInterator: operator* - Unused method"); }
    virtual bool operator==(const fwInterBase<T>& i) const {
        return typeid(*this) == typeid(i) && equal(i); }
    virtual bool operator!=(const fwInterBase<T>& i) const { return !((*this) == i); } 
protected:
    virtual bool equal(const fwInterBase<T>& i) const { return true; }
};


template <class T>
struct fInterator : public fwInterBase<T> {
protected:
    T       *pD;
public:
    fInterator() {}
    fInterator(T* ptr) : pD(p) {}
    ~fInterator() {}
    fwInterBase<T>* clone() { return new fInterator<T>(*this); }
    void operator+(unsigned int di) { pD += di; }
    void operator++() { pD++; } //prefix
    void operator++(int) { pD++; } //postfix
    T& operator*() {
        if (pD) return *pD;
        throw std::DSA_Exception(-100, "fInterator: operator* - Unused pointer");
    }
    bool operator==(const fwInterBase<T>& i) const {
        return typeid(*this) == typeid(i) && equal(i); }
    bool operator!=(const fwInterBase<T>& i) const { return !((*this) == i); }
protected:
    bool equal(const fwInterBase<T>& i) const {
        return pD == ((fInterator*)&i)->pD; 
    }
};

int main() {
    // DenseArray<int> *pL = new DenseArray<int>[100];

    return 0;
}