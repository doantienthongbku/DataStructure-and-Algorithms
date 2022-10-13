#include <iostream>
#include "list.h"
using namespace std;

#define defaultSize 10

template <class T>
class Node {
public:
    T element;
    Node* next;
    Node(const T& element, Node* next = nullptr) : element(element), next(next) { };
    Node(Node* next = nullptr) : next(next) { };
};


template <class T>
class LList : public List<T> {
private:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* curr;
    int size;

    void init() {
        curr = head = tail = new Node<T>;
        size = 0;
    }

    void removeAll() {
        while (head != nullptr) {
            curr = head;
            head = head->next;
            delete curr;
        }
    }
public:
    LList(int size = defaultSize) { init(); }
    ~LList() { removeAll(); }
    void print() const ;
    void clear() { removeAll(); init(); }

    //  Insert "it" at current position
    void insert(const T& it) {
        curr->next = new Node<T>(it, curr->next);
        if (tail == curr) tail = curr->next;    // new tail
        size++;
    }

    void append(const T& it) {
        tail = tail->next = new Node<T>(it, nullptr);
        size++;
    }

    // Remove and return current element
    T remove() {
        if (curr->next == nullptr) throw "No element";
        T it = curr->next->element;     // remember value
        Node<T>* item = curr->next;     // remember link node
        if (tail == curr->next) tail = curr;
        curr->next = curr->next->next;
        delete item;
        size--;
        return it;
    }

    void moveToStart() { curr = head; }
    void moveToEnd() { curr = tail; }

    void prev() {
        if (curr == head) return;
        Node<T>* temp = head;
        while (temp->next != curr) temp = temp->next;
        curr = temp;
    }

    void next() { if (curr != tail) curr = curr->next; }
    int length() { return size; }

    int currPos() const {
        Node<T>* temp = head;
        for (int i = 0; curr != temp; i++)
            temp = temp->next;
        return i;
    }

    void moveToPos(int pos) {
        if ((pos < 0) || (pos > size)) throw "Position out of range";
        curr = head;
        for (int i = 0; i < pos; i++) curr = curr->next;
    }

    const T& getValue() const {
        if (curr->next == nullptr) throw "No value";
        return curr->next->element;
    }
};

