#include <bits/stdc++.h>
using namespace std;


struct ListNode {
    int val;
    ListNode *left;
    ListNode *right;
    ListNode(int x = 0, ListNode *l = nullptr, ListNode* r = nullptr) : val(x), left(l), right(r) {}
};

/*
ListNode* reverse(ListNode* head, int a, int b) {
    /*Given the head of a doubly linked list, two positive integer a and b where a <= b.
     * Reverse the nodes of the list from position a to position b
     * and return the reversed list
     *
    ListNode* prev = nullptr;
    ListNode* curr = head;
    ListNode* next = nullptr;
    int count = 1;
    while (curr != nullptr && count < a) {
        prev = curr;
        curr = curr->right;
        count++;
    }
    ListNode* start = prev;
    ListNode* end = curr;
    while (curr != nullptr && count <= b) {
        next = curr->right;
        curr->right = prev;
        curr->left = next;
        prev = curr;
        curr = next;
        count++;
    }
    if (start != nullptr) {
        start->right = prev;
    }
    else {
        head = prev;
    }
    end->right = curr;
    if (curr != nullptr) {
        curr->left = end;
    }
    return head;
}
*/

ListNode* reverse(ListNode* head, int a, int b) {

}

int main() {
    int size;
    cin >> size;
    int* list = new int[size];
    for(int i = 0; i < size; i++) {
        cin >> list[i];
    }
    int a, b;
    cin >> a >> b;
    unordered_map<ListNode*, int> nodeValue;
    ListNode* head = init(list, size, nodeValue);
    ListNode* reversed = reverse(head, a, b);
    try {
        printList(reversed, nodeValue);
    }
    catch(char const* err) {
        cout << err << '\n';
    }
    freeMem(head);
    delete[] list;

    return 0;
}