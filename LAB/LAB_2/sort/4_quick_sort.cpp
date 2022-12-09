#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting {
private:
    static T* Partition(T* start, T* end) {
        T* pivot = end;
        T* i = start;
        T* j = start;
        while (j < end) {
            if (*j < *pivot) {
                swap(*i, *j);
                i++;
            }
            j++;
        }
        swap(*i, *pivot);
        return i;
    }
public:
    static void QuickSort(T* start, T* end) {
        if (start < end) {
            T* pivot = Partition(start, end);
            QuickSort(start, pivot - 1);
            QuickSort(pivot + 1, end);
        }
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