#include <iostream>
#include <vector>
using namespace std;

bool consecutiveOnes(vector<int>& nums) {
    if (nums.size() == 0) return true;

    for (int i = 1; i < nums.size(); i++)
        if (nums[i] == 1 && (nums[i] != nums[i - 1] && nums[i] != nums[i + 1])) return false;
    return true;
}

int main() {
    vector<int> nums {0, 1, 1, 1, 9, 8};
    // int i = 1;
    // cout << (nums[i] != nums[i - 1] || nums[i] != nums[i + 1]) << endl;
    cout << consecutiveOnes(nums) << endl;
    // vector<int> nums2 {};
    // cout << consecutiveOnes(nums2) << endl;

    return 0;
}