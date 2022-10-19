#include <iostream>
#include <stack>
#include <string>
using namespace std;

int baseballScore(string ops){
    stack<int> scores;
    int string_len = ops.length(), sum = 0;

    for (int i = 0; i < string_len; i++) {
        if ('0' <= ops[i] && '9' >= ops[i]) {
            int score = ops[i] - '0';
            scores.push(score);
        }
        else if (ops[i] == 'D') {
            scores.push(scores.top() * 2);
        }
        else if (ops[i] == 'C') {
            scores.pop();
        }
        else if (ops[i] == '+') {
            int score1 = scores.top();
            scores.pop();
            int score2 = scores.top();
            scores.push(score1);
            scores.push(score1 + score2);
        }
    }

    while (!scores.empty()) {
        sum += scores.top();
        scores.pop();
    }

    return sum;
}

int main() {
    cout << baseballScore("52CD+") << endl;

    return 0;
}