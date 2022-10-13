#include <iostream>
#include <string>
#include <sstream>
using namespace std;


template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;      // number of elements
public:
    SLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~SLinkedList() {}
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    void toString()
    {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
    
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
    };
};

template <class T>
void SLinkedList<T>::add(const T& e) {
    if (count == 0) {
        Node* newNode = new Node(e, nullptr);
        this->head = newNode;
        this->tail = newNode;
    } else {
        Node* newNode = new Node(e, nullptr);
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    if (count == 0){
        this->add(e);
    }
    else {
        if (index == 0){
            Node* newNode = new Node(e, head);
            this->head = newNode;
            this->count++;
        }
        else if (index == count) {
            this->add(e);
        }
        else {
            Node * p = head;
            while (index > 1) {
                p = p->next;
                index--;
            }
            Node* newNode = new Node(e, p->next);
            p->next = newNode;
            this->count++;
        }
    }
}

template<class T>
int SLinkedList<T>::size() {
    return count;
}

int main() {
    SLinkedList<int> list;
    int values[]   = {10, 15, 2,  6,  4,  7,  40,  8};
    int index[]    = {0,  0,  1,  3,  2,  3,  5,   0};
    
    for (int idx = 0; idx < 8; idx++){
        list.add(index[idx], values[idx]);
    }
        
    list.toString();
    

    return 0;
}