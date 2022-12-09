#include <iostream>
using namespace std;

long int midSquare(long int seed) {
    long int result = seed * seed;
    result = result % 1000000;
    result = result / 100;
    return result;
}

long int moduloDivision(long int seed, long int mod) {
    return seed % mod;
}

long int digitExtraction(long int seed, int* extractDigits, int size) {
    string digits = to_string(seed);
    string result = "";
    for (int i = 0; i < size; i++) result += digits[extractDigits[i]];
    return stoi(result);
}

int main() {
    int a[]={1,2,5};
    cout << digitExtraction(122443,a,3) << endl;
    cout <<midSquare(9452) << endl;

    return 0;
}