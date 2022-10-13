#include <iostream>
using namespace std;

template <class T>
void insertSort(T *pD, int n) {
    for (int i = 1; i < n; i++) {
        T temp(std::move(pD[i]));

        for (int j = i - 1; j > -1; j--) {
            if (pD[j] < temp) {
                pD[j] = std::move(temp);
                break;
            }
            else {
                pD[j + 1] = std::move(pD[j]);
            }
        }
    }
}
