#include <iostream>
using namespace std;

/*
pair<data_type1, data_type2> v;
make_pair(a, b) == {a, b}  (c++ 11.0 or newer)
v.first
v.second
*/

int main() {
    pair<int, int> v1 = {100, 200};
    pair<string, int> v2;

    cout << v1.first << " " << v1.second << endl;

    return 0;
}