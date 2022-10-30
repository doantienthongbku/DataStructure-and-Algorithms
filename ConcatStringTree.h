#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

class ConcatStringTree {
public:
    class Node {
    public:
        int leftlength;
        int length;
        Node* left;
        Node* right;
        char* data;
        friend class ConcatStringTree;
    public:
        Node()
        {
            leftlength=0; 
            length=0; 
            left=nullptr; 
            right=nullptr; 
            data=nullptr; 
        }
        Node(ConcatStringTree::Node& r);
        Node(const char* s);
        string toString();
        Node reverse();
    };
public:
    Node* root;
public:
    ConcatStringTree(){ root = new Node(); }
    ConcatStringTree(const char* s);
    int length() const;
    char get(int index);
    int indexOf(char c);
    string toStringPreOrder() const;
    string toString() const;
    ConcatStringTree concat(const ConcatStringTree& otherS) const;
    ConcatStringTree subString(int from, int to) const;
    ConcatStringTree reverse() const;

    int getParTreeSize(const string& query) const;
    string getParTreeStringPreOrder(const string& query) const;
public:
    // toStringPreorder supporter
    string NLR(Node* r) const;
};

#endif // __CONCAT_STRING_TREE_H__
