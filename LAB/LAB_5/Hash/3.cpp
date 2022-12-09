#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <unordered_map>
using namespace std;

// https://leetcode.com/problems/max-number-of-k-sum-pairs/solutions/961351/c-map-o-n-and-two-pointer-o-nlogn-easy-solution/

// using 2 pointers
/*int pairMatching(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int count = 0;
    int i = 0, j = nums.size() - 1;
    while (i < j) {
        if (nums[i] + nums[j] == target) {
            count++; i++; j--;
        }
        else if (nums[i] + nums[j] > target) j--;
        else i++;
    }

    return count;
}*/

// using map
int pairMatching(vector<int>& nums, int target) {
    map<int, int> map;
    int count = 0, len = nums.size();

    for (int i = 0; i < len; i++) {
        int res = target - nums[i];
        if (map.count(res)) {
            count++;
            if (map[res] == 1) map.erase(res);
            else map[res]--;
        }
        else {
            map[nums[i]]++;
        }
    }
    
    return count;
}

int main() {
    int target = 6;
    vector<int>items{4,4,2,1,2};
    cout << pairMatching(items, target) << endl;

    return 0;
}