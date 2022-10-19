#include <iostream>
using namespace std;


void printArray(int *arr, int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
}

void shellSort(int *pD, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int tmp = pD[i];
            int j = i - gap;
            while (j >= 0 && pD[j] > tmp) {
                pD[j + gap] = pD[j];
                j -= gap;
            }
            pD[j + gap] = tmp;
        }
        printArray(pD, n);
    }
}

int main() {
    int a[] = { 3, 2, 1, 5, 4 };
    shellSort(a, 5);
    printArray(a, 5);

    return 0;
}