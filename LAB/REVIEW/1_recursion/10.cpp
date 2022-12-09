#include <iostream>
using namespace std;

int mininumBracketAdd(string s) {
    if (s.length() <= 0) return 0;
    if (s[0] == '(' && s[s.length() - 1] == ')') return mininumBracketAdd(s.substr(1, s.length() - 2));
    if (s[0] == '(' && s[s.length() - 1] == '(') return 1 + mininumBracketAdd(s.substr(0, s.length() - 1));
    if (s[0] == ')' && s[s.length() - 1] == ')') return 1 + mininumBracketAdd(s.substr(1, s.length() - 1));
    if (s[0] == ')' && s[s.length() - 1] == '(') return 2 + mininumBracketAdd(s.substr(1, s.length() - 2));

    return 0;
}

int main() {
    cout << mininumBracketAdd(")))((") << endl;
    // output: 5

    return 0;
}
