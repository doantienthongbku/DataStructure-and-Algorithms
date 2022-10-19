#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <string>
using namespace std;

string removeDuplicates(string S){
    stack<char> s1, s2;
    int string_len = S.length();
    for(int i = 0; i < string_len; i++){
        s1.push(S[i]);
    }
    while(!s1.empty()){
        if(s2.empty()){
            s2.push(s1.top());
            s1.pop();
        }
        else{
            if(s2.top() == s1.top()){
                s2.pop();
                s1.pop();
            }
            else{
                s2.push(s1.top());
                s1.pop();
            }
        }
    }

    string ans = "";
    while(!s2.empty()){
        ans += s2.top();
        s2.pop();
    }
    return ans;
}

int main() {
    cout << removeDuplicates("abbaca") << endl;

    return 0;
}