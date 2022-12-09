#include "ConcatStringTree.h"

ConcatStringTree::Node::Node(ConcatStringTree::Node& r) {
    length = r.length;
    leftlength = r.leftlength;
    for (int i = 0; i < length; i++) {
        data[i] = (r.data)[i];
    }
    left = r.left;
    right = r.right;
}

ConcatStringTree::Node::Node(const char* s) {
    // Cap nhat leftlength
    leftlength = 0;
    // Do dai s va gan chuoi vao data
    length = 0;
    while (s[length] != '\0') length++;	// Dem do dai cua chuoi
    data = new char[length + 1];			// Do phuc tap giai thuat O(n)
    for (int i = 0; i < length; i++) data[i] = s[i]; 	// Deep copy
    data[length] = '\0';		// Ki tu ket thuc chuoi
    // Cac nhanh trai - phai
    left = nullptr;
    right = nullptr;
}

string ConcatStringTree::Node::toString() {
    stringstream ss;
    ss << "(LL=" << leftlength << ",L=" << length << ",";
    if (data == nullptr) ss << "<NULL>)";
    else ss << "\"" << data << "\")";
    return ss.str();
}

ConcatStringTree::Node ConcatStringTree::Node::reverse() {
    Node final;
    final.length = length;
    final.leftlength = length - leftlength;
    //cout << "?";
    if (data == nullptr) final.data = nullptr;
    else {
        final.data = new char[length];
        for (int i = 0; i < length; i++) {
            //cout << data[length - 1 - i];
            
            (final.data)[i] = data[length - 1 - i];
            //cout << final.data;
            //cout << "?";
        }
        final.data[length] = '\0';
        return final;
    }
    //cout << "?";
    if (right == nullptr) final.left = nullptr;
    else final.left = new Node(right->reverse());
    if (left == nullptr) final.right = nullptr;
    else final.right = new Node(left->reverse());
}

ConcatStringTree::ConcatStringTree(const char* s) {
    this->root = new Node(s);
}

int ConcatStringTree::length() const {
    //..................
    return 0;
}

char ConcatStringTree::get(int index) {
    if (index < 0 || index > root->length - 1) throw out_of_range("Index of string is invalid!");
    Node* curr = root;
    while (curr->data == nullptr) {
        if (index < curr->leftlength) curr = curr->left;
        else 
        {
            index -= curr->leftlength;
            curr = curr->right;
        }
    }
    return (curr->data)[index];
}

string ConcatStringTree::NLR(Node* r) const{
    // TODO: return the sequence of values of nodes in pre-order.
    string str = "";
    if (r == nullptr) return "";
    // first print data of node
    if (r == root) str += r->toString();
    else
    {
        str += ",";
        str += r->toString();
    }
    //then recur on left sutree
    str += NLR(r->left);
    //now recur on right subtree 
    str += NLR(r->right);
    return str;
}

string ConcatStringTree::toStringPreOrder() const{
    string s = "[";
    s += NLR(root);
    s += "]";
    return NLR(root);
}

ConcatStringTree ConcatStringTree::concat(const ConcatStringTree& otherS) const {
    ConcatStringTree finalTree;
    finalTree.root->left = this->root;
    finalTree.root->right = otherS.root;
    finalTree.root->length = this->root->length + otherS.root->length;
    finalTree.root->leftlength = this->root->length;
    return finalTree;
}

ConcatStringTree ConcatStringTree::reverse() const {
    ConcatStringTree final;
    //cout << "?";
    Node* p = new Node(root->reverse());
    //cout << "?";
    final.root = p;
    return final;
}
