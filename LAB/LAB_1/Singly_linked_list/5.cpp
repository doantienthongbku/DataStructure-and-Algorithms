#include <iostream>
using namespace std;

class LLNode {
public:
    int val;
    LLNode* next;
    LLNode(); // Constructor: val = 0, next = nullptr
    LLNode(int val, LLNode* next); // Constructor with customized data
};

LLNode* reverseLinkedList(LLNode* head) {
    /*The function returns the head of the reversed linked list.*/
    LLNode* prev = nullptr;
    LLNode* curr = head;
    LLNode* next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}