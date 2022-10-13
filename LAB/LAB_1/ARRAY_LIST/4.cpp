#include <iostream>
#include <vector>
using namespace std;

int longestSublist(vector<string>& words) {
    /*The function returns the length of the longest subarray where all words share the same first letter.*/
    if (words.size() == 0) return 0;
    int max_sub = 0;
    for (int i = 0; i < words.size(); i++) {
        char first_letter = words[i][0];
        int count = 1;
        for (int j = i+1; j < words.size(); j++)
            if (words[j][0] == first_letter)
                count++;
        
        if (count > max_sub) max_sub = count;
    }
    
    return max_sub;
}

int main() {
    vector<string> words {"faction", "fight", "and", "are", "attitude"};
    cout << longestSublist(words) << "\n";

    return 0;
}
