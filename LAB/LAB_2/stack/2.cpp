#include <iostream>
#include <stack>
#include <vector>

vector<int> nextGreater(vector<int>& arr){
    vector<int> returnstack = arr;
    for (unsigned int i = 0; i < arr.size(); i++){
        returnstack[i] = -1;
        for (unsigned int j = i+1; j < arr.size(); j++){
            if (arr[j] > arr[i]) {
                returnstack[i] = arr[j];
                break;
            }
        }
    }
    return returnstack;
}