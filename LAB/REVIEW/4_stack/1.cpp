#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        int len = s.length();
        for (int i = 0; i < len; i++) {
            if (s[i] == '-') continue;
            if (!isdigit(s[i])) return false;
        }
        return true;
    }

    int calPoints(vector<string>& operations) {
        stack<int> scores;
        for (auto oper : operations) {
            cout << oper << endl;
            if (isNumber(oper)) {
                int score = std::stoi(oper);
                scores.push(score);
            }
            else if (oper == "D") {
                int score = scores.top() * 2;
                scores.push(score);
            }
            else if (oper == "C") { scores.pop(); }
            else if (oper == "+") {
                int score1 = scores.top();
                scores.pop();
                int score2 = scores.top();
                scores.push(score1);
                scores.push(score1 + score2);
            }
        }

        int sum_score = 0;
        while (!scores.empty()) {
            sum_score += scores.top();
            scores.pop();
        }

        return sum_score;
    }
};

int main() {
    vector<string> ops = {"5","-2","4","C","D","9","+","+"};
    Solution solution;
    cout << solution.calPoints(ops) << endl;

    return 0;
}