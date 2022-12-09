#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <climits>
using namespace std;

int sumOfMaxSubarray(vector<int>& nums, int k) {
    deque<int> nums_dq, tmp_dq;
    int result = 0, max_s = 0;
    
    for (int i = 0; i < k; i++) if (max_s < nums[i]) max_s = nums[i]; 
    nums_dq.push_back(max_s);
    
    for (int i = k + 1; k < nums.size(); k++) {
        
    }
}

int main() {
    vector<int> nums {1, 2, 4, 3, 6};
    int k = 3;
    cout << sumOfMaxSubarray(nums, k);

    return 0;
}