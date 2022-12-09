#include <iostream>
#include <queue>
using namespace std;

template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    
    //Helping functions go here
    static void heapify(T *elements, int N, int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < N && elements[left] > elements[smallest]) smallest = left;
        if (right < N && elements[right] > elements[smallest]) smallest = right;
        if (smallest != index) {
            T temp = elements[index];
            elements[index] = elements[smallest];
            elements[smallest] = temp;
            Sorting<T>::heapify(elements, N, smallest);
        }
    }

    static void heapSort(T* start, T* end){
        int num_ele = end - start;
        // build heap (rearrange array)
        for (int i = num_ele / 2 - 1; i >= 0; i--)  // from parent to root
            Sorting<T>::heapify(start, num_ele, i);

        for (int i = num_ele - 1; i > 0; i--) {
            // Move current root to end
            swap(start[0], start[i]);

            // call max heapify on the reduced heap
            Sorting<T>::heapify(start, i, 0);
        }

        Sorting<T>::printArray(start,end);
    }  
};



int main() {
    int arr[4]={4,2,9,1};
    Sorting<int>::heapSort(&arr[0],&arr[4]);

    int arr2[4]={-1,0,2,3};
    Sorting<int>::heapSort(&arr2[0],&arr2[4]);

    return 0;
}