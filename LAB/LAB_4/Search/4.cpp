#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>

bool findPairs(int arr[], int n, pair<int,int>& pair1, pair<int, int>& pair2)
{
   // TODO: If there are two pairs satisfy the condition, assign their values to pair1, 
   // pair2 and return true. Otherwise, return false.
    std::map<int, int> map;
    for (int i = 0; i < n; i++) {
        if (map.find(arr[i]) != map.end()) {
            pair1.first = map[arr[i]];
            pair1.second = i;
            pair2.first = map[arr[i]];
            pair2.second = i;
            return true;
        }
        map[arr[i]] = i;
    }
    return false;
}


int main() {
    int arr[] = { 3, 4, 7, 1, 2, 9, 8 };
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2)) {
        if (checkAnswer(arr, n, pair1, pair2)) {
            printf("Your answer is correct.\n");
        }
        else printf("Your answer is incorrect.\n");
    }
    else printf("No pair found.\n");
}