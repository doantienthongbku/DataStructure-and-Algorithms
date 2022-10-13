#include <iostream>
#include <string.h>
using namespace std;

int myArrayToInt(char *str, int n) 
{ 
    if (n == 0) return 0;
    return (str[n-1] - '0') + 10 * myArrayToInt(str, n - 1);
}

int main() {
    char str[] = "2020";
    printf("%d", myArrayToInt(str, 4));

    return 0;
}