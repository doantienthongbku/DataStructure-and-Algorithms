#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

int foldShift(long long key, int addressSize) {
    string key_str = std::to_string(key);
    long long sum = 0, key_len = key_str.length();
    for (int i = 0; i < key_len; i += addressSize) {
        string sub_key = key_str.substr(i, addressSize);
        sum += std::stoll(sub_key);
    }
    long long tmp = (pow(10, addressSize));
    return (sum % tmp) ;
}

int rotation(long long key, int addressSize) {
    string key_str = std::to_string(key);
    rotate(key_str.begin(), key_str.end() - 1, key_str.end());
    return foldShift(std::stoll(key_str), addressSize);
}

int main() {
    cout << rotation(1234567891234, 5) << endl;

    return 0;
}