#ifndef __MIN_HEAP__

#include <iostream>
#include<climits>
using namespace std;

void swap(int *x, int *y);

class MinHeap {
public:
    int *items;
    int capacity;
    int count;
public:
    MinHeap(int capacity);
    void MinHeapify(int i);  // to heapify a subtree with the root at given index
    int parent(int i);      // get parent
    int left(int i);        // get index of left child of node at index i
    int right(int i);       // get index of right child of node at index i
    int extractMin();       // extract the root which is the minimum element
    void decreaseKey(int i, int new_val);   // Decreases key value of key at index i to new_val
    int getMin();           // Returns the minimum key (key at root) from min heap
    void deleteKey(int i);  // Deletes a key stored at index i
    void insertKey(int i);  // Insert a new key 'i'
    void printItems();
};

#endif