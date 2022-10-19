#include <iostream>
using namespace std;

int f(int x){
    return ((x > 0) ? x*f(x-1): 2);
}

void convert(int num, char*& oct) {
    // convert number to octal
    int i = 0;
    while (num > 0) {
        int tmp = num % 8;
        oct[i] = tmp + '0';
        num /= 8;
        i++;
    }
    oct[i] = '\0';
}

int main() {
    char* oct = new char[100];
    convert(132, oct);
    for (int i = 0; i < 100; i++) {
        cout << oct[i];
    }
    cout << endl;

    return 0;
}