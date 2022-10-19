#ifndef STACK_H
#define STACK_H
#include "DLinkedList.h"

template<class T>
class Stack {
protected:
    DLinkedList<T> list;
public:
    Stack() {}
    void    push(T item) ;
    T       pop() ;
    T       top() ;
    bool    empty() ;
    int     size() ;
    void    clear() ;
};

template <class T>
void Stack<T>::push(T item) {
    // TODO: Push new element into the top of the stack
    this->list.add(0, item);
}

template <class T>
T Stack<T>::pop() {
    // TODO: Remove an element on top of the stack
    this->list
}

template <class T>
T Stack<T>::top() {
    // TODO: Get value of the element on top of the stack
        
}

template <class T>
bool Stack<T>::empty() {
    // TODO: Determine if the stack is empty
        
}

template <class T>
int Stack<T>::size() {
    // TODO: Get the size of the stack
        
}

template <class T>
void Stack<T>::clear() {
    // TODO: Clear all elements of the stack
    
}

#endif