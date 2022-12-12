#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap() {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap() { delete[]elements; }
    void push(T item);
    void remove(T item);
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    int getItem(T item);
    void clear();
    
    void printHeap() {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }
private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};

template<class T>
int Heap<T>::size() { return count; }

template<class T>
bool Heap<T>::isEmpty() { return (count == 1); }

template<class T>
T Heap<T>::peek() {
    if (count == 0) return -1;
    return elements[0];
}

template<class T>
bool Heap<T>::contains(T item) {
    if (count == 0) return false;
    for (int i = 0; i < count; i++)
        if (elements[i] == item) return i;
    return -1;
}

template<class T>
bool Heap<T>::pop() {
    if (count == 0) return false;
    elements[0] = elements[count - 1];
    count--;
    reheapDown(0);
    return true;
}

template<class T>
void Heap<T>::push(T item) {
    ensureCapacity(count + 1);
    elements[count] = item;
    reheapUp(count);
    count++;
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity) {
    if (minCapacity > capacity) {
        T* old_eles = elements;
        capacity = capacity * 2;
        elements = new T[capacity];
        for (int i = 0; i < count; i++)
            elements[i] = old_eles[i];
        delete[] old_eles;
    }
}

template<class T>
void Heap<T>::reheapUp(int position) {
    int parent = (position - 1) / 2;
    while (elements[position] > elements[parent]) {
        T temp = elements[position];
        elements[position] = elements[parent];
        elements[parent] = temp;
        reheapUp(parent);
    }
}

template<class T>
void Heap<T>::reheapDown(int position) {
    int left = position * 2 + 1;
    int right = position * 2 + 2;
    int smallest = position;

    if (elements[left] > elements[position]) smallest = left;
    if (elements[right] > elements[position]) smallest = right;
    if (smallest != position) {
        T temp = elements[position];
        elements[position] = elements[smallest];
        elements[smallest] = temp;
        reheapDown(smallest);
    }
}

template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int )
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
}



int main() {
    Heap<int> maxHeap;
    int arr[] = {42,35,30,15,20,21,18,3,7,14};
    for (int i = 0; i < 10; i++)
        maxHeap.push(arr[i]);
    maxHeap.remove(42);
    maxHeap.remove(35);
    maxHeap.remove(30);
    maxHeap.printHeap();

    return 0;
}