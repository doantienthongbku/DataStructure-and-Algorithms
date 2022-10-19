#include <iostream>
using namespace std;

string reverseSentence(string s) {
    /*The function returns the reverse of the sentence s by recursion*/
    if (s.length() == 0) return "";
    int i = s.find(" ");
    if (i == -1) return s;
    return reverseSentence(s.substr(i + 1)) + " " + s.substr(0, i);
}

int main() {
    cout << reverseSentence("data structure and algorithm is scary") << endl;

    return 0;
}