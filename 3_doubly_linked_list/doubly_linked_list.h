#include <iostream>
#include <string>
#include <sstream>
using namespace std;


template <class T>
class DLinkedList {
public:
    class Iterator; //forward declaration
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
    void    sort();
    Iterator begin() { return Iterator(this, true); }
    Iterator end() { return Iterator(this, false); }

public:
    class Node {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;
        Iterator begin() { return Iterator(this, true); }
        Iterator end() { return Iterator(this, false); }

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

    class Iterator {
    private:
        DLinkedList<T> *pList;
        Node *current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);
        void remove();
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
    };
};
