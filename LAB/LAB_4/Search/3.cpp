#include <iostream>
#include <math.h>
using namespace std;


int jumpSearch(int arr[], int x, int n) {
    // TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n) - 1] < x) {
        cout << prev << " ";
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }
    while (arr[prev] < x) {
        cout << prev << " ";
        prev++;
        if (prev == min(step, n))
            return -1;
    }
    if (arr[prev] == x) {
        cout << prev << " ";
        return prev;
    }
    return -1;
}


int main() {
    int arr[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610 };
    int x = 55;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);

    if (index != -1) {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else {
        cout << "\n" << x << " is not in array!";
    }
    cout << endl;

    return 0;
}