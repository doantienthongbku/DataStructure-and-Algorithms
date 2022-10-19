#include <iostream>
using namespace std;


void printArray(int *arr, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}


void quickSort(int* arr, int size) {
    if (size <= 1) {
        return;
    }
    int pivot = arr[size - 1];
    int i = 0;
    int j = size - 2;
    while (i <= j) {
        while (i <= j && arr[i] <= pivot) {
            i++;
        }
        while (i <= j && arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i];
    arr[i] = arr[size - 1];
    arr[size - 1] = temp;
    quickSort(arr, i);
    quickSort(arr + i + 1, size - i - 1);
}


int main() {
    int a[] = { 3, 2, 1, 5, 4 };
    quickSort(a, 5);
    printArray(a, 5);

    return 0;
}