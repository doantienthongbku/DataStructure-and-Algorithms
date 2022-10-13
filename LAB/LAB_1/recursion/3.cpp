#include  <iostream>
using namespace std;

int findMax(int* arr, int length)
{
    if (length == 1) return arr[0];
    int max = findMax(arr, length - 1);
    if (max > arr[length - 1]) return max;
    else return arr[length - 1];
}

int main() {
    int arr[] = {10, 5, 7, 9, 15, 6, 11, 8, 12, 2};
    cout << findMax(arr, 10) << endl;
    int arr2[] = {10, 5, 7, 9, 11, 6, 14, 8, 12, 2};
    cout << findMax(arr2, 10) << endl;

    return 0;
}