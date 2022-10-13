#include <iostream>
#include <vector>
using namespace std;

int computeSum(vector<int>& nums, int start, int end) {
    /*The function returns the sum of the elements in the vector nums from index start to index end.*/
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += nums[i];
    }
    return sum;
}

int equalSumIndex(vector<int>& nums) {
    if (nums.size() == 0) return -1;
    if (nums.size() == 1) return 0;

    for (int i = 0; i < nums.size(); i++) {
        if (computeSum(nums, 0, i) == computeSum(nums, i + 1, nums.size())) {
            return i;
        }
    }
    return -1;
}

int main() {
    vector<int> nums {3, 5, 2, 7, 6, 4};
    cout << equalSumIndex(nums) << endl;

    return 0;
}