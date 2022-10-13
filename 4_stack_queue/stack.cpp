#include <iostream>
using namespace std;


/* STACK IMPLEMENTATION */

template <class T>
class Stack {
public:
    Stack() {}
    Stack(const Stack<T>& ) {}
    Stack(Stack<T>&& ) {}
    virtual ~Stack() {}

    virtual int size() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual Stack<T> operator=(Stack<T>& ) = 0;
    virtual Stack<T> operator=(Stack<T>&& ) = 0;

    virtual void push(const T&) = 0;
    virtual void push(const T&&) = 0;
    virtual void pop() = 0;
    virtual T& top() = 0;
    virtual const T& getTop() const = 0;
};


template <class T>
class DenseStack : public Stack<T> {
public:


    void resize(int N) override { DenseList::resize(N); }
    
};