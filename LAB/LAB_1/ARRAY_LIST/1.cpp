#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<int>& vector) {
    cout << "[";
    for (int i = 0; i < vector.size() - 1; i++)
        cout << vector[i] << " ";
    cout << vector[vector.size() - 1] << "]";
}

vector<int> updateArrayPerRange(vector<int>& nums, vector<vector<int>>& operations) {
    for (auto & ele : operations)
        for (int i = ele[0]; i <= ele[1]; i++)
            nums[i] += ele[2];

    return nums;
}


int main() {
    vector<int> nums {13, 0, 6, 9, 14, 16};
    vector<vector<int>> operations {{5, 5, 16}, {3, 4, 0}, {0, 2, 8}};
    vector<int> hehe = updateArrayPerRange(nums, operations);
    printVector(hehe); cout << endl;

    return 0;
}