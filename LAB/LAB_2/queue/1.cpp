#include <iostream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;

int sumOfMaxSubarray(vector<int>& nums, int k) {
    deque<int> dq;
    int sum = 0, max_q = 0, vec_size = nums.size();
    for (int i = 0; i < k; i++) {
        if (dq.empty()) dq.push_back(i);
        else {
            while (!dq.empty() && nums[dq.back()] < nums[i])
                dq.pop_back();
            dq.push_back(i);
        }
    }
    sum = nums[dq.front()];

    for (int i = k; i < vec_size; i++) {
        if (i - k + 1 > dq.front()) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i])
            dq.pop_back();
        dq.push_back(i);
        sum += nums[dq.front()];
    }

    return sum;
}

int main() {
    vector<int> nums {1, 2, 4, 3, 6};
    int k = 3;
    cout << sumOfMaxSubarray(nums, k) << endl;

    return 0;
}