#include <iostream>
using namespace std;

void printHailstone(int number) {
    if (number == 1) {
        cout << number;
        return;
    }
    if (number % 2 == 0) {
        cout << number << " ";
        printHailstone(number / 2);
    } else {
        cout << number << " ";
        printHailstone(number * 3 + 1);
    }
}

int main() {
    printHailstone(32);

    return 0;
}