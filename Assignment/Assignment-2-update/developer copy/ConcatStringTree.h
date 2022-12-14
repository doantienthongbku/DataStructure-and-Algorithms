#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

bool approved(const string& query);

class ConcatStringTree {
public:
    class Identity {
    public:
        unsigned int key;
    public:
        Identity();
        unsigned int value();
        void update();
    };
    static Identity id;
public: // ParentsTree
    enum BalanceFactor { LH = -1, EH = 0, RH = 1 };
    class ParentsTree {
    public:
        class pNode {
        public:
            pNode *pLeft;
            pNode *pRight;
            unsigned int key;
            BalanceFactor balance;
            friend class ParentsTree;
        public:
            pNode();
            pNode(unsigned int value);
            string toStringPreOrder();  
        };
    public:
        pNode *root;
        int count;
    public:
        ParentsTree();
        int size() const;
        string toStringPreOrder() const;

        void insertAVL(const unsigned int value);
        void remove(const unsigned int& value);
    public:
        // helper functions
        pNode* insertAVLRec(pNode *node, unsigned int value, bool &taller);
        int getHeightRec(pNode *node);
        int getBalanceFactor(pNode *node);
        pNode* rotL(pNode *node);
        pNode* rotR(pNode *node);
        pNode* balanceLeft(pNode *node, bool &taller);
        pNode* balanceRight(pNode *node, bool &taller);

        pNode* minValueNode(pNode* node);
        pNode* maxValueNode(pNode* node);

        pNode* LLRotation(pNode* node);
        pNode* RRRotation(pNode* node);
        pNode* LRRotation(pNode* node);
        pNode* RLRotation(pNode* node);
        pNode* deleteNodeRec(pNode* node, unsigned int key);

        string toStringPreOrderRec(pNode* node) const;
    };
public:
    class Node {
    public:
        int leftLength;
        int length;
        Node* pLeft;
        Node* pRight;
        char* data;
        unsigned int key;
        ParentsTree AVL;
        friend class ConcatStringTree;
    public:
        Node();
        Node(const ConcatStringTree::Node& r);
        Node(const char* s);
        ~Node();
        int indexOfNode(char c);
        string toStringNode();
        string toStringPreOrderNode();
        Node subStringNode(int from, int to);
        Node reverseNode();
    };
public:
    Node* root;
public:
    ConcatStringTree();
    ConcatStringTree(const char * s);
    ~ConcatStringTree();
    int length() const;
    char get(int index);
    int indexOf(char c);
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree & otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;

    int getParTreeSize(const string & query) const;
    string getParTreeStringPreOrder(const string & query) const;
public:
    // support functions
    string traverseNLR(Node* node, bool only_str) const;
    void indexOfRec(Node* node, char c, int &index);
};

class ReducedConcatStringTree; // forward declaration
class LitStringHash; // forward declaration

class HashConfig {
private:
    int p;          // use in hash function
    double c1, c2;  // use in quadratic function
    double lambda;  // load factor
    double alpha;   // extend factor
    int initSize;   // size of hash

    friend class ReducedConcatStringTree;
    friend class LitStringHash;
public:
    HashConfig();
    HashConfig(int p, double c1, double c2, double lambda, double alpha, int initSize);
};

class LitStringHash {
public:
    HashConfig config;
    int count;
    char** items;
    int lastInsertedIndex;
public:
    LitStringHash(HashConfig & hashConfig);
    ~LitStringHash();
    int getLastInsertedIndex() const;
    string toString() const;
public:
    int hashFunction(const char* s) const;
    int quadraticFunction(const char* s, int index) const;
    void hashInsert(const char* s);
    void hashInsert(const char* s, char** listItems);
    int hashSearch(const char* s);
    bool hashRemove(const char* s);
    void hashClear();
    void rehashingTable();
    bool isEmpty();
    // helper functions
    int pow(int a, int b) const;
    bool strCompare(char* s1, char* s2);
    void freeItem(char *item) const;
};

class ReducedConcatStringTree : public ConcatStringTree {
public:
    ReducedConcatStringTree(const char * s, LitStringHash * litStringHash);
    LitStringHash * litStringHash;
public:
    Node *root;
public:
    // ~ReducedConcatStringTree();
    int length() const;
    char get(int index);
    int indexOf(char c);
    string toStringPreOrder() const;
    string toString() const;
    // ReducedConcatStringTree concat(const ReducedConcatStringTree & otherS) const;
    // ReducedConcatStringTree subString(int from, int to) const;
    // ReducedConcatStringTree reverse() const;

    // int getParTreeSize(const string & query) const;
    // string getParTreeStringPreOrder(const string & query) const;
// public:
    // support functions
    string traverseNLR(Node* node, bool only_str) const;
    void indexOfRec(Node* node, char c, int &index);
};

#endif // __CONCAT_STRING_TREE_H__