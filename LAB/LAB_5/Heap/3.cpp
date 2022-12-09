#include <iostream>
using namespace std;

void reheapDown(int maxHeap[], int numberOfElements, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < numberOfElements && maxHeap[left] > maxHeap[index]) smallest = left;
    if (right < numberOfElements && maxHeap[right] > maxHeap[index]) smallest = right;
    if (smallest != index) {
        int temp = maxHeap[index];
        maxHeap[index] = maxHeap[smallest];
        maxHeap[smallest] = temp;
        reheapDown(maxHeap, numberOfElements, smallest);
    }
}

void reheapUp(int maxHeap[], int numberOfElements, int index) {
    int parent = (index - 1) / 2;
    
    if (maxHeap[index] > maxHeap[parent]) {
        int temp = maxHeap[index];
        maxHeap[index] = maxHeap[parent];
        maxHeap[parent] = temp;
        reheapUp(maxHeap, numberOfElements, parent);
    }
}

int main() {


    return 0;
}