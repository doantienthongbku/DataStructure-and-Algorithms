#include <iostream>
using namespace std;

int interpolationSearch(int arr[], int left, int right, int x) {
    // implement interpolation search in this function
    // return the index of the element if found
    // if not found, return -1

    if (left <= right && x >= arr[left] && x <= arr[right]) {
        int pos = left + (((double)(right - left) / (arr[right] - arr[left])) * (x - arr[left]));
        cout << "We traverse on index: " << pos << endl;
        if (arr[pos] == x)
            return pos;
        if (arr[pos] > x)
            return interpolationSearch(arr, left, pos - 1, x);
        return interpolationSearch(arr, pos + 1, right, x);
    }
    return -1;
}

int main() {
    int arr[] = { 1, 5, 7, 8, 16, 30, 33, 35, 41, 49, 51, 52, 59, 61, 65, 68, 69, 71, 72, 75, 76, 83, 85, 89, 97 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 49;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                : cout << "Element is present at index " << result;
    cout << endl;

    return 0;
}