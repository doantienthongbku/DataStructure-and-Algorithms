#include <iostream>
#include <functional>
#include <iomanip>
using namespace std;


template <class T, int N>
class NWTree {
protected:
    struct Node;
    struct Entry {
        T data;
        Node *pRight;
        Entry(const T & val, Node *pR = nullptr) : data(val), pRight(pR) {}
    };
    struct Node {
        Node *pLeft;
        Entry e[N - 1];
        size_t nE;
    };
    Node *pRoot;
public:

}