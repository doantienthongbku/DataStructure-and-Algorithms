#include <iostream>
#include <vector>
using namespace std;

int longestSublist(vector<string>& words) {
    if (words.size() <= 0) return 0;
    int max_sub = 0, count = 0, len = words.size(), i = 0;
    while (i < len) {
        char first_letter = words[i][0];
        i++; count = 1;
        for (int j = i; j < len; j++) {
            if (words[j][0] == first_letter) { count++; if (max_sub < count) max_sub = count; }
            else {
                count = 0; i = j; break;
            }
        }
    }

    return max_sub;
}

int main() {
    vector<string> words {"faction", "fight", "and", "are", "attitude", "bdcjsb", "attit"};
    cout << longestSublist(words) << endl;

    return 0;
}