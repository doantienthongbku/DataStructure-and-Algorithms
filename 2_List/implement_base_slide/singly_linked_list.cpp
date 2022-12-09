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
    class Iterator;

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
    void    reverse();

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

    class Iterator
    {
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
        void remove();
        
        // Prefix ++ overload
        Iterator &operator++();
        
        // Postfix ++ overload
        Iterator operator++(int);
    };
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
        Node* temp = this->head;
        this->head = this->head->next;
        this->count--;
        T data = temp->data;
        delete temp;
        return data;
    } else if (index == this->count - 1) {
        Node* p = this->head;
        while (p->next != this->tail) {
            p = p->next;
        }
        Node* temp = this->tail;
        this->tail = p;
        this->tail->next = nullptr;
        this->count--;
        T data = temp->data;
        delete temp;
        return data;
    } else {
        Node* p = this->head;
        while (index > 1) {
            p = p->next;
            index--;
        }
        Node* temp = p->next;
        p->next = p->next->next;
        this->count--;
        T data = temp->data;
        delete temp;
        return data;
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

template <class T>
void SinglyLinkedList<T>::reverse() {
    Node* p = this->head;
    Node* q = nullptr;
    Node* r = nullptr;
    this->tail = this->head;
    while (p != nullptr) {
        r = q;
        q = p;
        p = p->next;
        q->next = r;
    }
    this->head = q;
}

/*
----------------------------------------------------------------------------------
-----------------------------------INTERATOR--------------------------------------
----------------------------------------------------------------------------------
*/


template <class T>
SinglyLinkedList<T>::Iterator::Iterator(SinglyLinkedList<T>* pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true: 
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false: 
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
    this->pList = pList;
    if (begin) {
        if (pList != NULL) {
            this->current = pList->head;
            this->index = 0;
        } else {
            this->current = NULL;
            this->index = -1;
        }
    } else {
        this->current = NULL;
        if (pList != NULL) this->index = pList->size();
        else this->index = 0;
    }
}

template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;

    return *this;
}

template <class T>
void SinglyLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
    */
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
    if (this->index == 0) {
        this->pList->removeAt(0);
        this->current = NULL;
        this->index = -1;
    } else {
        this->pList->removeAt(this->index);
        this->current = this->pList->head;
        this->index = 0;
        while (this->index < this->index - 1) {
            this->current = this->current->next;
            this->index++;
        }
    }
}

template <class T>
void SinglyLinkedList<T>::Iterator::set(const T& e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
    this->current->data = e;
}

template <class T>
T& SinglyLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
    return this->current->data;
}

template <class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    /*
        Operator not equals
        * Returns false if two iterators points the same node and index
    */
    return (this->current != iterator.current || this->index != iterator.index);
}
// Prefix ++ overload
template <class T>
typename SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    if (this->index == this->pList->size()) throw std::out_of_range("Segmentation fault!");
    if (this->current == NULL) this->current = this->pList->head;
    else this->current = this->current->next;
    this->index++;
    return *this;
}
// Postfix ++ overload
template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    if (this->index == this->pList->size()) throw std::out_of_range("Segmentation fault!");
    if (this->current == NULL) this->current = this->pList->head;
    else this->current = this->current->next;
    this->index++;
    return *this;
}



int main() {



    return 0;
}