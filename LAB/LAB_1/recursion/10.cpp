#include <iostream>
using namespace std;

int mininumBracketAdd(string s) {
    /*Given a string s consisting only of '(' and ')'.
    returns the mininum number of brackets needed to be inserted to s so that the brackets are balanced
    */
    if (s.length() == 0) return 0;
    if (s[0] == ')') return 1 + mininumBracketAdd(s.substr(1));
    else {
        int i = (s).find(')');
        if (i >= 0 && i < s.length()) return mininumBracketAdd(s.substr(1, i - 1) + s.substr(i + 1));
        else return 1 + mininumBracketAdd(s.substr(1));
    }
}

int main() {
    cout << mininumBracketAdd(")())(((())()())()())))()()))(()((((()(()()()))()((())((()))))))()(((()(((())(((()()(())(())))))(()))") << endl;

    return 0;
}