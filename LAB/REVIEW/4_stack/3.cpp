#include <iostream>
#include <stack>
#include <sstream>
#include <unordered_map>
using namespace std;

// class Solution {
// public:
//     string removeDuplicateLetters(string s) {
//         stack<char> result;
//         stack<char> tmp_stack;
//         int len = s.length();

//         for (int i = 0; i < len; i++) {
//             if (result.empty()) result.push(s[i]);
//             else {
//                 if (s[i] == result.top()) continue;
//                 else if (s[i] < result.top()) result.push(s[i]);
//                 else {
//                     while (!result.empty() && s[i] > result.top()) {
//                         tmp_stack.push(result.top());
//                         result.pop();
//                     }
//                     if (result.empty()) {
//                         if (s[i] != tmp_stack.top()) result.push(s[i]);
//                         while (!tmp_stack.empty()) {
//                             result.push(tmp_stack.top());
//                             tmp_stack.pop();
//                         }
//                     } else {
//                         if (s[i] < result.top()) result.push(s[i]);
//                         while (!tmp_stack.empty()) {
//                             result.push(tmp_stack.top());
//                             tmp_stack.pop();
//                         }
//                     }
//                 }
//             }
//         }

//         stringstream stream;
//         while (!result.empty()) { stream << result.top(); result.pop(); }

//         return stream.str(); 
//     }
// };

class Solution {
public:
    string removeDuplicateLetters(string s) {
        int len = s.size();
        string res = "";
        unordered_map<char, int> M;
        unordered_map<char, bool> V;
        stack<int> S;
        
        for (auto c : s) {
            if (M.find(c) == M.end()) M[c] = 1;
            else M[c]++; 
        }
        for (unordered_map<char, int>::iterator iter=M.begin(); iter!=M.end(); iter++) V[iter->first] = false;
        
        cout<<M.size()<<V.size()<<endl;
        for (int i=0; i<len; i++) {
            M[s[i]]--;
            if (V[s[i]] == true) continue;
            
            while (!S.empty() and s[i] < s[S.top()] and M[s[S.top()]] > 0) {
                V[s[S.top()]] = false;
                S.pop();
            }
            S.push(i);
            V[s[i]] = true;
        }
        while (!S.empty()) {
            res = s[S.top()] + res;
            S.pop();
        }
        return res;
    }
};

int main() {
    string s = "cbacdcbc";
    Solution solution;
    cout << solution.removeDuplicateLetters(s) << endl;

    return 0;
}