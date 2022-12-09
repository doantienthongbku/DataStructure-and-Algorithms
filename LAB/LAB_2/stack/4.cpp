#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;

bool isValidParentheses (string s) {
    stack<char> s1;
    for (int i = 0; i < s.length(); i++) {
        if (s1.empty()) s1.push(s[i]);
        else {
            if ((s[i] == ')' && s1.top() == '(') || (s[i] == ']' && s1.top() == '[') || (s[i] == '}' && s1.top() == '{'))
                s1.pop();
            else s1.push(s[i]);
        }
    }
    return s1.empty();
}

int main() {
    cout << isValidParentheses("[]()") << endl; // 1

    return 0;
}