#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* append(Node* head, int data);
int getSize(Node* head);
void print(Node* head);
Node* insertAt(Node* head, int position, int data);
Node* removeAt(Node* head, int position);
int getAt(Node* head, int position);
bool setAt(Node* head, int position, int data);

int main() {
    Node* head = nullptr;
    head = append(head, 2);
    head = append(head, 3);
    head = append(head, 5);
    head = append(head, 4);
    head = insertAt(head, 7, 100);
    print(head);
    head = removeAt(head, 4);
    print(head);
    return 0;
}

Node* append(Node* head, int data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;

    // if linked list is empty
    if (head == nullptr) {
        head = newNode;
        return head;
    }

    // loop while get end of linked list & append node
    Node* p = head;
    while (p->next != nullptr) {
        p = p->next;
    }
    p->next = newNode;

    return head;
}

int getSize(Node* head) {
    int count = 0;
    Node* p = head;
    while (p != nullptr) {
        count++;
        p = p->next;
    }

    return count;
}

void print(Node* head) {
    Node* p = head;
    cout << "[";
    while (p != nullptr) {
        cout << p->data << " -> ";
        p = p-> next;
    }
    cout << "null]" << endl;
}

int getAt(Node* head, int position) {
    Node* p = head;
    while (position > 0 && p != nullptr) {
        p = p->next;
        position--;
    }
    if (p == nullptr || position < 0) throw range_error("Invalid access");
    return p->data;
}

bool setAt(Node* head, int position, int data) {
    Node* p = head;
    while (position > 0 && p != nullptr) {
        p = p->next;
        position--;
    }
    if (p == nullptr || position < 0) return false;
    p->data = data;
    return true;
}

Node* insertAt(Node* head, int position, int data) {
    if (head == nullptr) return append(head, data);
    Node* p = head;

    // if position is negative, insert at the head of the linked list
    if (position <= 0) {
        head = new Node;
        head->next = p;
        head->data = data;

        return head;
    }

    while (position > 1 && p != nullptr) {
        position--;
        p = p->next;
    }

    // if position > len, insert at the end of the linked list
    if (p == nullptr) return append(head, data);

    // normal insert data
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = p->next;
    p->next = newNode;

    return head;
}

Node* removeAt(Node* head, int position) {
    Node* p = head;
    if (position < 0 || position >= getSize(head)) throw range_error("Invalid access");
    if (position == 0) head = p->next;
    else {
        while (position > 1 && p != nullptr) {
            p = p->next;
            position--;
        }
        p->next = p->next->next;
    }

    return head;
}
