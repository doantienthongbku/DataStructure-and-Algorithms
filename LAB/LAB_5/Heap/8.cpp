#include <bits/stdc++.h>
using namespace std;

// int leastAfter(vector<int>& nums, int k) {
//     for (int i = 0; i < k; i++) {
//         sort(nums.begin(), nums.end());
//         nums[0] = nums[0] * 2;
//     }
//     sort(nums.begin(), nums.end());
//     return nums[0];
// }

int leastAfter(vector<int>& nums, int k) {
    make_heap(nums.begin(), nums.end(), greater<int>());
    for (auto x : nums) cout << x << " ";
    cout << endl;
    cout << "================" << endl;

    for (int i = 0; i < 3; i++) {
        int tmp = nums.front() * 2;

        nums.push_back(tmp);
        for (auto x : nums) cout << x << " ";
        cout << endl;

        push_heap(nums.begin(), nums.end(), greater<int>());
        for (auto x : nums) cout << x << " ";
        cout << endl;

        nums.erase(nums.begin());
        for (auto x : nums) cout << x << " ";
        cout << endl;
        
        cout << "================" << endl;
    }
    
    
    return nums.front();
}

int main() {
    vector<int> nums {1, 3, 3, 2};
    int k = 4;
    cout << leastAfter(nums, k) << endl;

    return 0;
}