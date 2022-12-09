#include <iostream>
#include <vector>
using namespace std;

int equalSumIndexRec(vector<int>& nums, int& leftsum, int& rightsum) {
    
}

int equalSumIndex(vector<int>& nums) {
    if (nums.size() == 0) return -1;
    if (nums.size() == 1) return 0;
    if (nums.size() == 2) return -1;
    int leftsum = 0, rightsum = 0;
    equalSumIndexRec(nums, leftsum, rightsum);
}

int main() {
    vector<int> nums {3, 5, 2, 7, 6, 4};
    cout << equalSumIndex(nums);

    return 0;
}