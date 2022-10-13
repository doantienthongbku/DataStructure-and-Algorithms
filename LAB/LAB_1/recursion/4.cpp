#include  <iostream>
#include <string.h>
using namespace std;

/* Style substr
bool isPalindrome(string str) 
{ 
    if (str.length() == 0 || str.length() == 1) return true;
    if (str[0] == ' ') return isPalindrome(str.substr(1, str.length() - 1));
    if (str[str.length() - 1] == ' ') return isPalindrome(str.substr(0, str.length() - 1));
    if (str[0] != str[str.length()-1]) return false;
    return isPalindrome(str.substr(1, str.length()-2));
} */

bool isPalRec(string str, int left, int right) {
    if (left >= right - 1) return true;
    if (str[left] == ' ') return isPalRec(str, left + 1, right);
    if (str[right] == ' ') return isPalRec(str, left, right - 1);
    if (str[left] != str[right]) return false;
    return isPalRec(str, left + 1, right - 1);
}

bool isPalindrome(string str) 
{ 
    return isPalRec(str, 0, str.length() - 1);
}

int main() {
    cout << isPalindrome("mom") << endl;
    cout << isPalindrome("do geese see god") << endl;

    return 0;
}