#include <iostream>
#include "algorithm"
using namespace std;

int buyCar(int* nums, int length, int k) {
    /* find maximum cars can buy with an amount of money k,
        * and return the maximum number of cars can buy
        * nums: array of prices of cars
        * length: length of nums
        * k: amount of money
        */
    int max_cars = 0;
    sort(nums, nums + length);
    for (int i = 0; i < length; i++) {
        if (k >= nums[i]) {
            k -= nums[i];
            max_cars++;
        }
    }

    return max_cars;
}

int main() {
    int nums[] = {90,30,40,90,20};
    int length = sizeof(nums)/sizeof(nums[0]);
    cout << buyCar(nums, length, 90) << "\n";

    return 0;
}