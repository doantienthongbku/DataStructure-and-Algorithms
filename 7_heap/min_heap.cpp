#include "min_heap.h"

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// =========================================================

MinHeap::MinHeap(int capacity) {
    this->count = 0;
    this->capacity = capacity;
    this->items = new int[capacity];
}

void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    
    if (l < count && items[l] < items[i])   smallest = l;
    if (r < count && items[r] < items[i])   smallest = l;
    if (smallest != i) {
        swap(&items[i], &items[smallest]);
        MinHeapify(smallest);
    } 
}

int MinHeap::parent(int i) { return (i - 1) / 2; }

int MinHeap::left(int i) { return (2 * i + 1); }

int MinHeap::right(int i) { return (2 * i + 2); }

int MinHeap::getMin() { return items[0]; }

void MinHeap::insertKey(int k) {
    if (this->count == this->capacity) throw std::out_of_range("Overflow!!!");
    
    count++;
    int i = count - 1;
    items[i] = k;

    // fix if value is item < parent
    while (i != 0 && items[parent(i)] > items[i]) {
        swap(&items[i], &items[parent(i)]);
        i = parent(i);
    }
}

void MinHeap::decreaseKey(int i, int new_val) {
    this->items[i] = new_val;
    // fix if value is item < parent
    while (i != 0 && items[parent(i)] > items[i]) {
        swap(&items[i], &items[parent(i)]);
        i = parent(i);
    }
}

int MinHeap::extractMin() {
    if (count <= 0) return INT_MAX;
    if (count == 1) { count--; return items[0]; }

    // Store the minimum value, and remove it from heap
    int root = items[0];
    items[0] = items[count - 1];
    count--;
    MinHeapify(0);

    return root;
}

void MinHeap::deleteKey(int i) {
    decreaseKey(i, INT_MIN);
    extractMin();
}

void MinHeap::printItems() {
    for (int i = 0; i < capacity; i++) cout << items[i] << " ";
    cout << endl;
}

int main() {
    MinHeap h(11);
    h.insertKey(3);
    h.insertKey(2);
    h.deleteKey(1);
    h.insertKey(15);
    h.insertKey(5);
    h.insertKey(4);
    h.insertKey(45);
    h.printItems();

    cout << h.extractMin() << " ";
    cout << h.getMin() << " ";
    h.decreaseKey(2, 1);
    cout << h.getMin();
    cout << endl;

    return 0;
}
