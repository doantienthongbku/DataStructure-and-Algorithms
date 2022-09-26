#include <iostream>
#include <set>
using namespace std;

/*
Complexity of set: O(log(n))
Characteristic:
    - set have no duplicate elements
    - set order is sorted from small to large
Method
    - insert
    - size
    - find
    - count
    - s.begin(), s.end()
*/


int main() {
    set<int> s;
    // s.insert(100);
    // s.insert(200);
    // s.insert(300);
    // s.insert(100);
    // s.insert(200);
    // cout << s.size() << endl;   // size = 3, s = (100, 200, 300)

    for (int i = 0; i < 10; i++) {
        s.insert(i);
    }
    cout << "Size = " << s.size() << endl;

    // // count
    // if (s.count(5) != 0) cout << "Found!\n";
    // else cout << "Not Found!\n";
    
    if (s.find(5) != s.end()) cout << "Found!\n";
    else cout << "Not Found!\n";


    return 0;
}