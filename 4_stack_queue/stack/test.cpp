#include "DLinkedList.h"

int main() {
    DLinkedList<int> list;
    int size = 10;
    int value[] = {2,5,6,3,67,332,43,1,0,9};

    for(int idx=0; idx < size; idx++){
    list.add(value[idx]);
    }
    list.removeAt(9);
    cout << list.toString() << endl;

    return 0;
}