#include <iostream>
#include <stack>
using namespace std;

class QueueS {
private:
    stack<int> s1, s2;
    
public:
    void enqueue(int value) {
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        
        s2.push(value);
        
        while(!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }
    int dequeue() {
        if (s1.empty()) throw out_of_range("Empty queue");
        int data = s1.top();
        s1.pop();
        
        return data;
    }
    int front() {
        if (s1.empty()) throw out_of_range("Empty queue");
        return s1.top();
    }
    int rear() {
        if (s1.empty()) throw out_of_range("Empty queue");
        
        while(!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        
        int data = s2.top();
        
        while(!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
        
        return data;
    }
    
    string toString() {
        string out = "";
        out += "FRONT|";
        while(!s1.empty()) {
            s2.push(s1.top());
            out += " " + std::to_string(s1.top());
            s1.pop();
        }
        
        while(!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
        out += "|REAR";
        
        return out;
    }
};