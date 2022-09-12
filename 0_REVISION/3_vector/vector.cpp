#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// vector<int> v;

/*
.push_back(value): add element to the end
v[i] == *(v.begin() + i): access the element at index i / v[v.size() - 1] == v.back()  
.size(): size of vector
LOOP:
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << endl;
    }
    for (auto it = v.begin(); it != v.end(); ++it) {        --> slower
        cout << *it << endl;
    }
    for (auto & element : vector) {
        element.doSomething ();
    }
*/

void printVector(vector<int> v) {
    cout << "[";
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << "]" << endl;
}

int main() {
    // vector<int> v;
    // v.push_back(10);
    // v.push_back(20);
    // v.push_back(30);

    // cout << "Size = " << v.size() << endl;
    // cout << "v[2] = " << v[2] << endl;
    // cout << "v[2] = " << *(v.begin() + 2) << endl;
    // cout << "v[end_element] = " << v.back() << endl;

    // for (auto it = v.begin(); it != v.end(); ++it) {
    //     cout << *it << endl;
    // }

    // Initialized vector
    // int n; cin >> n;
    // vector<int> v;
    // for (int i = 0; i < n; i++) {
    //     int x; cin >> x;
    //     v.push_back(x);
    // }
    // cout << "Size = " << v.size() << endl;
    // printVector(v);

    // vector<int> v2(5, 3); // khoi tao vector voi 5 phan tu gia tri = 3 (default = 0)

    // push a string to the vector
    string s = "python programing language";
    stringstream ss(s);
    string tmp;
    vector<string> v;
    while (ss >> tmp) {
        v.push_back(tmp);
    }

    for (string x : v) {
        cout << x << endl;
    }

    return 0;
}