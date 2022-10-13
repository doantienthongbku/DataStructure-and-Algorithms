#include  <iostream>
using namespace std;

void printArray(int n)
{
    if (n == 0) cout << n;
    else if (n >= 1) {
        printArray(n-1);
        cout << ", " << n;
    }
}

int main() {
    printArray(10);
    cout << endl;

    return 0;
}