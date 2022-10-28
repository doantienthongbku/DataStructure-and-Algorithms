#include "ConcatStringTree.h"

ConcatStringTree::Node::Node(const char* s) {
    // Cap nhat leftlength
    leftlenght = 0;
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


ConcatStringTree::ConcatStringTree(const char* s) {
    this->root = new Node(s);
}

int ConcatStringTree::length() const {
    return 0;
}
char ConcatStringTree::get(int index) {
    if (index < 0 || index > root->length - 1) throw out_of_range("Index of string is invalid!");
    Node* curr = root;
    while (curr->data == nullptr) {
        if (index < curr->leftlenght) curr = curr->left;
        else 
        {
            index -= curr->leftlenght;
            curr = curr->right;
        }
    }
    return (curr->data)[index];
}
