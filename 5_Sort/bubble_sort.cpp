#include <iostream>
using namespace std;

void printArray(int *arr, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}

void bubbleSort(int* pD, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (pD[j] > pD[j + 1]) {
                int temp = pD[j];
                pD[j] = pD[j + 1];
                pD[j + 1] = temp;
            }
        }
        printArray(pD, n);
    }
}


int main() {
    int a[] = {8, 22, 7, 9, 31, 19, 5, 13};
    bubbleSort(a, 8);

    return 0;
}