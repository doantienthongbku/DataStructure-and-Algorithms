#include <iostream>
using namespace std;


void printArray(int *arr, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}

void selectionSort(int* pD, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (pD[j] < pD[min]) {
                min = j;
            }
        }
        int temp = pD[i];
        pD[i] = pD[min];
        pD[min] = temp;
        printArray(pD, n);
    }
}

int main() {
    int a[] = { 3, 2, 1, 5, 4 };
    selectionSort(a, 5);

    return 0;
}