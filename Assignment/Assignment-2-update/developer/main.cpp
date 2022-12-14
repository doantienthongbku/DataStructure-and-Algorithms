#include "ConcatStringTree.h"

// g++ -o main main.cpp ConcatStringTree.cpp -I . -std=c++11

int main() {
	/*Test case 2 - ParentStringTree for ReducedConcatStringTree*/
    HashConfig hashConfig(
        2,
        0.5,
        0.5,
        0.75,
        2,
        4
    );

    LitStringHash * litStringHash = new LitStringHash(hashConfig);
    
    // test concat() and destructor
    ReducedConcatStringTree *s1 = new ReducedConcatStringTree("hello", litStringHash);
    ReducedConcatStringTree *s2 = new ReducedConcatStringTree("_world_", litStringHash);
    ReducedConcatStringTree *s3 = new ReducedConcatStringTree("hello", litStringHash);
    ReducedConcatStringTree *s4 = new ReducedConcatStringTree("_Khanh", litStringHash);
    cout << endl << litStringHash->toString() << endl << endl;

    ReducedConcatStringTree *s5 = new ReducedConcatStringTree(s1->concat(*s2));
    ReducedConcatStringTree *s6 = new ReducedConcatStringTree(s3->concat(*s4));
    ReducedConcatStringTree *s7 = new ReducedConcatStringTree(s5->concat(*s6));

    cout << "s7 ParentsTree: " << s7->root->AVL.toStringPreOrder() << endl << endl;

    cout << "s1.concat(s3): " << s1->concat(*s3).toString() << endl;
    cout << "s1.concat(s3): " << s1->concat(*s3).toStringPreOrder() << endl;
    cout << endl;

    cout << "s7.length(): " << s7->length() << endl;
    cout << "s7: " << s7->toString() << endl;
    cout << "s7: " << s7->toStringPreOrder() << endl;
    cout << endl;

    const string s = "r";
    try { 
        cout << "s1 getParTreeSize: " << s2->getParTreeSize(s) << endl;
        cout << "s1 getParTreeStringPreOrder: " << s2->getParTreeStringPreOrder(s) << endl;
    }
    catch (runtime_error& rt) { cout << rt.what() << endl; }
    
    delete s1;
    delete s2;
    delete s3;
    delete s6;
    delete s4;
    delete s5;
    delete s7;
    delete litStringHash;

    return 0;
}