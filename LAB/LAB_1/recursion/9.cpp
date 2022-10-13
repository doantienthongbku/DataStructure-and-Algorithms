#include <iostream>
using namespace std;

int findGCD(int a, int b) {
    if (a == b) return a;
    else {
        if (a > b) return findGCD(a - b, b);
        else return findGCD(a, b - a);
    }
}

int findLCM(int a, int b)
{
    return (a * b) / findGCD(a, b);
}

int main() {
    cout << findLCM(10, 102) << endl;

    return 0;
}