#include <iostream>
#include "list.h"
using namespace std;

#define defaultSize 10

template <class T>
class DenseList : public List<T> {
private:
    int maxSize;
    int listSize;
    int curr;
    T* listArray;   // Array holding list elements
public:
    DenseList(int size=defaultSize) {
        maxSize = size;
        listSize = 0;
        listArray = new T[maxSize];
    }

    ~DenseList() { delete[] listArray; }    // destructor

    void clear() {
        delete[] listArray;
        listSize = 0;
        listArray = new T[maxSize]; // Recreate array
    }

    void insert(const T& it) {
        if (listSize > maxSize) throw "List capacity exceeded";
        for (int i = listSize; i > curr; i--)
            listArray[i] = listArray[i - 1];
        listArray[curr] = it;
        listSize++;
    }

    void append(const T& it) {
        if (listSize > maxSize) throw "List capacity exceeded";
        listArray[listSize++] = it;
    }

    // Remove and return the current element.
    T remove() {
        if ((curr < 0) || (curr > listSize)) throw "No element";
        T it = listArray[curr];     // copy the element
        for (int i=curr; i < listSize - 1; i++)
            listArray[i] = listArray[i + 1];
        listSize--;
        return it;
    }

    void moveToStart() { curr = 0; }
    void moveToEnd() { curr = listSize; }
    void prev() { if (curr != 0) curr--; }
    void next() { if (curr < listSize) curr++; }

    int length() const { return listSize; }
    int currPos() const { return curr; }
    void moveToPos(int pos) {
        if ((currPos() < 0) || (currPos() > listSize)) throw "Pos out of range";
        curr = pos;
    }

    const T& getValue() const {
        if ((curr < 0) || (curr > listSize)) throw "No current element";
        return listArray[curr];
    }

    void print() {
        cout << "[ ";
        for (moveToStart(); currPos() < length(); next())
            cout << getValue() << " ";
        cout << "]" << endl;
    }
};

int main() {
    cout << "Dense Array: " << endl;
    DenseList<int> arr(10);
    arr.append(10);
    arr.append(20); 
    arr.append(30); 
    arr.append(40);
    arr.print();

    return 0;
}


