#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

template <class T>
class BaseList {
public:
    virtual void add(T e) = 0;
    virtual void add(int index, T e) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(T item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, T e) = 0;
    virtual int indexOf(T item) = 0;
    virtual bool contains(T item) = 0;
    virtual void toString() = 0;
};


template <class T>
class SinglyLinkedList : public BaseList<T> {
public:
    class Node;
    // class Iterator;

protected:
    Node* head;
    Node* tail;
    int count;
public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~SinglyLinkedList() { this->clear(); };
    void    add(T element);
    void    add(int index, T element);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, T element);
    int     indexOf(T item);
    bool    contains(T item);
    T       removeAt(int index);
    bool    removeItem(T item);
    void    clear();
    void    dump ();
    void    toString();

public:
    class Node {
    protected:
        T data;
        Node* next;
        friend class SinglyLinkedList<T>;
    public:
        Node() : next(nullptr) {}
        Node(Node* data) : data(data), next(nullptr) {}
        Node(T data, Node* next) : data(data), next(next) {}
    };

    /*class Iterator {
    private:
        SinglyLinkedList<T> *pList;
        Node *current;
        int index; // corresponding with current node
    public:
        Iterator(SinglyLinkedList<T> *pList, bool begin);
        Iterator &operator=(const Iterator &iterator);
        void set(const T &e);
        T &operator*();
        bool operator!=(const Iterator &iterator);

        Iterator &operator++();
        Iterator operator++(int);
    };*/
};


template <class T>
void SinglyLinkedList<T>::toString() {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

template <class T>
void SinglyLinkedList<T>::add(T element) {
    if (count == 0) {
        Node* newNode = new Node(element, nullptr);
        this->head = newNode;
        this->tail = newNode;
    } else {
        Node* newNode = new Node(element, nullptr);
        this->tail->next = newNode;
        this->tail = newNode;
    }
    this->count++;
}

template<class T>
void SinglyLinkedList<T>::add(int index, T e) {
    if (this->count == 0) this->add(e);
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
            Node * p = this->head;
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


template <class T>
int SinglyLinkedList<T>::size() { return this->count; }

template<class T>
bool SinglyLinkedList<T>::empty() { return (this->count == 0); }

template <class T>
T SinglyLinkedList<T>::get(int index) {
    if (index < 0 || index >= this->count) throw std::out_of_range("Index out of range");
    Node * p = this->head;
    while (index > 0) {
        p = p->next;
        index--;
    }
    return p->data;
}

template <class T>
void SinglyLinkedList<T>::set(int index, T element) {
    if (index < 0 || index >= this->count) throw std::out_of_range("Index out of range");
    Node * p = this->head;
    while (index > 0) {
        p = p->next;
        index--;
    }
    p->data = element;
}

template <class T>
int SinglyLinkedList<T>::indexOf(T item) {
    int index = 0;
    Node* p = this->head;
    while (p != nullptr) {
        if (p->data == item) return index;
        p = p->next;
        index++;
    }
    return -1;
}

template <class T>
bool SinglyLinkedList<T>::contains(T item) {
    return (this->indexOf(item) != -1);
}

template <class T>
T SinglyLinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= this->count) throw std::out_of_range("Index out of range");
    if (index == 0) {
        T data_removed = this->head->data;
        this->head = this->head->next;

        return data_removed;
    }
    else if (index == this->count - 1) {
        Node * p = this->head;
        while (p->next->next != nullptr) {
            p = p->next;
        }
        T data_removed = p->next->data;
        p->next = nullptr;
        this->tail = p;

        return data_removed;
    }
    else {
        Node * p = this->head;
        while (index > 1) {
            p = p->next;
            index--;
        }

        T data_removed = p->next->data;
        p->next = p->next->next;
        this->count--;

        return data_removed;
    }
}

template <class T>
bool SinglyLinkedList<T>::removeItem(T item) {
    int index = this->indexOf(item);
    if (index == -1) return false;
    else {
        this->removeAt(index);
        return true;
    }
}

template <class T>
void SinglyLinkedList<T>::clear() {
    while (this->head != nullptr) {
        Node* p = this->head;
        head = head->next;
        delete p;
    }
    this->count = 0;
}


int main() {
    SinglyLinkedList<int> list;
    assert( list.size() == 0 );

    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(idx);
    }
    assert( list.size() == size );

    int values[]   = {10,  15,  2,   6,  4,  7,   40,  8};
    //                0    1    2    3   4   5    6    7
    int index[]    = {0,   1,   5,   3,  2,  1,   1,   0};

    /*                10,  15,  2,   6,  4,  7,   40,  8 //initial list
        *                15,  2,   6,   4,  7,  40,  8      //after removeAt 0
        *                15,  6,   4,   7,  40, 8      //after removeAt 1
        *                15,  6,   4,   7,  40   //after removeAt 5
        *                15,  6,   4,   40   //after removeAt 3
        *                15,  6,   40   //after removeAt 2
        *                15,  40   //after removeAt 1
        *                15,   //after removeAt 1
        *                {}  //after removeAt 0
        */
    int expvalues[][8]= {
        {15,  2,   6,   4,  7,  40,  8},
        {15,  6,   4,   7,  40, 8},
        {15,  6,   4,   7,  40},
        {15,  6,   4,   40 },
        {15,  6,   40},
        {15,  40},
        {15},
        {}
    };

    list.clear();
    assert( list.size() == 0 );
    assert( list.empty() == true );
    //
    for(int idx=0; idx < 8; idx++)
        list.add(values[idx]);
    assert( list.size() == 8 );

    //removeAt:
    int count = 8;
    for(int idx=0; idx < 8; idx++){
        int idxRemoved = index[idx];
        list.removeAt(idxRemoved);
        assert( list.size() == (count - idx -1) );
        //check expected values
        for(int c=0; c < (count - idx -1); c++ ){
            int exp = expvalues[idx][c];
            assert(exp == list.get(c));
        }
    }


    return 0;
}