#include <iostream>
#include <string>
#include <sstream>
using namespace std;


template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DLinkedList() { this->clear(); }
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item);
    string  toString();
    T       removeAt(int index);
    bool    removeItem(const T &item);
    void    clear();
    void    reverse();

public:
    class Node {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;

    public:
        Node() {
            this->previous = NULL;
            this->next = NULL;
        }
        Node(const T &data) {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
};


template <class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    if (head == nullptr) {
        head = new Node(e);
        tail = head;
    } else {
        Node* newNode = new Node(e);
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    this->count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */ 
    if (index < 0 || index > this->count) throw std::out_of_range("Index out of range");

    if (index == (this->count) || this->head == nullptr) {
        this->add(e);
    }
    else if (index == 0) {
        Node* newNode = new Node(e);
        newNode->next = this->head;
        newNode->previous = nullptr;
        this->head = newNode;

        this->count++;
    } 
    else {
        Node* p = this->head;
        while (index > 1) {
            p = p->next;
            index--;
        }
        Node* newNode = new Node(e);
        newNode->next = p->next;
        newNode->previous = p;
        p->next->previous = newNode;
        p->next = newNode;
        
        this->count++;
    }
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */ 
    return this->count;
}


template <class T>
string DLinkedList<T>::toString() {
    string result = "[";
    Node* p = this->head;
    while (p) {
        result += std::to_string(p->data) + " ";
        p = p->next;
    }
    result += "]";
    return result;
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    if (index < 0 || index >= this->count) throw std::out_of_range("Index out of range");
    Node* p = this->head;
    while (index > 0) {
        p = p->next;
        index--;
    }
    return p->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index < 0 || index >= this->count) throw std::out_of_range("Index out of range");
    Node* p = this->head;
    while (index > 0) {
        p = p->next;
        index--;
    }
    p->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return (this->count == 0);
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    if (this->count == 0) return -1;
    Node* p = this->head; int index = 0;
    while (p) {
        if (p->data == item) return index;
        index++; p = p->next;
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    return (this->indexOf(item) != -1);
}

template <class T>
T DLinkedList<T>::removeAt(int index) {
    /* Remove the element at given index in the list */
    if (index < 0 || index >= this->count) throw std::out_of_range("Index out of range");
    if (index == 0) {
        Node* p = this->head;
        this->head = this->head->next;
        this->head->previous = nullptr;
        T data = p->data;
        delete p;
        this->count--;
        return data;
    }
    else if (index == (this->count - 1)) {
        Node* p = this->tail;
        this->tail = this->tail->previous;
        this->tail->next = nullptr;
        T data = p->data;
        delete p;
        this->count--;
        return data;
    }
    else {
        Node* p = this->head;
        while (index > 0) {
            p = p->next;
            index--;
        }
        p->previous->next = p->next;
        p->next->previous = p->previous;
        T data = p->data;
        delete p;
        this->count--;
        return data;
    }
}

template <class T>
bool DLinkedList<T>::removeItem(const T &item) {
    /* Remove the first occurrence of item in the list */
    int index = this->indexOf(item);
    if (index == -1) return false;
    this->removeAt(index);
    return true;
}

template <class T>
void DLinkedList<T>::clear() {
    /* Remove all elements in the list */
    if (this->count == 0) return;
    Node* p = this->head;
    while (p) {
        Node* q = p;
        p = p->next;
        delete q;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

template <class T>
void DLinkedList<T>::reverse() {
    // reverse doubly linked list
    if (this->count == 0) return;
    Node* p = this->head;
    while (p) {
        Node* q = p->next;
        p->next = p->previous;
        p->previous = q;
        p = q;
    }
}