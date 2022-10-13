#ifndef __BASE_LIST_
#define __BASE_LIST_


#include <iostream>
using namespace std;

template <class T>
class List {
private:
    void operator=(const List&); // Protect assignment
    List(const List&);
public:
    List() { }
    virtual ~List() { }

    virtual void clear() = 0;
    virtual void insert(const T& item) = 0;
    virtual void append(const T& item) = 0;
    virtual T remove() = 0;
    virtual int length() const = 0;

    // Set the current position to the start of the list
    virtual void moveToStart() = 0;
    // Set the current position to the end of the list
    virtual void moveToEnd() = 0;
    // Move the current position one step left. No ch ange if already at beginning
    virtual void prev() = 0;
    // Move the current position one step right. No change if already at end
    virtual void next() = 0;
    // Return: The position of the current element
    virtual int currPos() const = 0;
    // Set current position.
    // pos: The position to make current.
    virtual void moveToPos(int pos) = 0;
    // Return: The current element
    virtual const T& getValue() const = 0;
};

/* interation of the list:
    for (L.moveToStart(); L.currPos()<L.length(); L.next()) {
        it = L.getValue();
        doSomething(it);
    }
*/


#endif // __BASE_LIST__