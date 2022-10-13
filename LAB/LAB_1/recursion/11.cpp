#include <iostream>
using namespace std;

string* splitBySpace(string s) {
    string* result = new string[2];
    int i = 0;
    while (s[i] != ' ') {
        result[0] += s[i];
        i++;
    }
    i++;
    while (i < s.length()) {
        result[1] += s[i];
        i++;
    }
    return result;
}

// string reverseSentence(string s) {

// }

int main() {
    string a = "data structure and algorithm is scary";
    string* result = splitBySpace(a);
    for (int i = 0; i < 2; i++) {
        cout << result[i] << endl;
    }

    return 0;
}