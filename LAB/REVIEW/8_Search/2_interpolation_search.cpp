#include <iostream>
using namespace std;

int interpolationSearch(int arr[], int left, int right, int x) {
    
}

int main() {
    int arr[] = { 1,2,3,4,5,6,7,8,9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 3;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                : cout << "Element is present at index " << result;

    return 0;
}