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
    ~Heap() { delete[] elements; }
    
    void push(T item);
    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    int getItem(T item);
    void remove(T item);
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

//Your code goes here

template<class T>
int Heap<T>::size() { return count; }

template<class T>
bool Heap<T>::isEmpty() { return (count == 0); }

template<class T>
T Heap<T>::peek() {
    if (count == 0) return -1;
    return elements[0];
}

template<class T>
bool Heap<T>::contains(T item) {
    for (int i = 0; i < count; i++)
        if (elements[i] == item) return true;
    return false;
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
        T* old = elements;
        capacity = 2 * capacity;
        elements = new T[capacity];
        for (int i = 0; i < count; i++)
            elements[i] = old[i];
        delete[] old;
    }
}

template<class T>
void Heap<T>::reheapUp(int position) {
    int parent = (position - 1) / 2;
    if (elements[position] > elements[parent]) {
        T temp = elements[position];
        elements[position] = elements[parent];
        elements[parent] = temp;
        reheapUp(parent);
    }
}

template<class T>
void Heap<T>::reheapDown(int position) {
    int left = (position * 2 + 1);
    int right = (position * 2 + 2);
    int smallest = position;

    if (left < count && elements[left] > elements[position]) smallest = left;
    if (right < count && elements[right] > elements[position]) smallest = right;
    if (smallest != position) {
        int temp = elements[smallest];
        elements[smallest] = elements[position];
        elements[position] = temp;
        reheapDown(smallest);
    }
}

template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int i = 0; i < count; i++)
        if (elements[i] == item) return i;
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    if (count == 0) return;
    if (count == 1) { count--; return; } 
    int index = getItem(item);
    if (index != count - 1) elements[index] = elements[count - 1];
    count--;
    reheapDown(index);
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    for (int i = 0; i < count; i++) elements[i] = 0;
    count = 0;
}


int main() {
    Heap<int> maxHeap;
    int arr[] = { 13, 19, 20, 7, 15, 12, 16, 10, 8, 9, 3, 6, 18, 2, 14, 1, 17, 4, 11, 5 };
    for (int i = 0; i < 20; ++i)
        maxHeap.push(arr[i]);
    maxHeap.clear();
    maxHeap.printHeap();

    return 0;
}