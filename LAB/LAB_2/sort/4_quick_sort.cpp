#include <sstream>
#include <iostream>
#include <type_traits>


using namespace std;
template <class T>
class Sorting {
private:
    static T* Partition(T* start, T* end) {
        // TODO: return the pointer which points to the pivot after rearrange the array.
        int pivot = *start;
        int size = end - start;

        int count = 0;
        for (int i = 1; i <= size; i++) {
            if (*(start + i) <= pivot)
                count++;
        }
    
        int pivotIndex = count;
        swap(*(start + pivotIndex), *start);
    
        int i = 0, j = size;
        while (i < pivotIndex && j > pivotIndex) {
            while (*(start + i) <= pivot) i++;
            while (*(start + j) > pivot) j--;
    
            if (i < pivotIndex && j > pivotIndex)
                swap(start[i++], start[j--]);
        }
    
        return (start + pivotIndex);
    }

public:
    static void QuickSort(T* start, T* end) {
        // must print out the index of pivot in subarray after everytime calling method Partition.
        if (start >= end) return;   
        T* pivot = Partition(start, end);
        cout << pivot - start << " ";
        QuickSort(start, pivot - 1);
        QuickSort(pivot + 1, end);
    }
};

int main() {
    int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
    cout << "Index of pivots: ";
    Sorting<int>::QuickSort(&array[0], &array[20]);
    cout << "\n";
    cout << "Array after sorting: ";
    for (int i : array) cout << i << " ";
    cout << "\n";

    return 0;
}