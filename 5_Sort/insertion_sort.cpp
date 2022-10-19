#include <iostream>
using namespace std;


void printArray(int *arr, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}

void insertionSort(int *pD, int n) {
    for (int i = 1; i < n; i++) {
        int temp = pD[i];
        int j = i - 1;
        while (j >= 0 && pD[j] > temp) {
            pD[j + 1] = pD[j];
            j--;
        }
        pD[j + 1] = temp;
        printArray(pD, n);
    }
}


int main() {
    int a[] = { 3, 2, 1, 5, 4 };
    insertionSort(a, 5);
    printArray(a, 5);

    return 0;
}