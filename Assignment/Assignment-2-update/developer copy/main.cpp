#include "ConcatStringTree.h"

// g++ -o main main.cpp ConcatStringTree.cpp -I . -std=c++11

int main() {
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        10
    );
    LitStringHash * litStringHash = new LitStringHash(hashConfig);
    ReducedConcatStringTree * s1 = new ReducedConcatStringTree("hello_", litStringHash);
    ReducedConcatStringTree * s2 = new ReducedConcatStringTree("Xuan_", litStringHash);
    ReducedConcatStringTree * s3 = new ReducedConcatStringTree("Huong_", litStringHash);

    cout << litStringHash->toString() << endl;
    cout << "getLastInsertedIndex: " << litStringHash->getLastInsertedIndex() << endl;

    // test length
    cout << "s1 length: " << s1->length() << endl;
    cout << "s2 length: " << s2->length() << endl;

    // test get() function
    cout << "s1 get(): ";
    for (int i = 0; i < s1->length(); i++) cout << s1->get(i) << " ";
    cout << endl;
    cout << "s2 get(): ";
    for (int i = 0; i < s2->length(); i++) cout << s2->get(i) << " ";
    cout << endl;
    // cout << s1->get(4);

    // test indexOf()
    cout << "Index of 'n' in s2: " << s2->indexOf('n') << endl;

    // test constructor
    ReducedConcatStringTree * s4 = new ReducedConcatStringTree("hello_", litStringHash);
    cout << "getLastInsertedIndex: " << litStringHash->getLastInsertedIndex() << endl;
    cout << litStringHash->toString() << endl;

    // test toStringPreOrder() and toString()
    cout << "s1 toString: " << s1->toString() << endl;
    cout << "s1 toStringPreOrder: " << s1->toStringPreOrder() << endl;

    delete s3;
    delete s1;
    delete s2;
    delete litStringHash;

    return 0;
}