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
    ~DLinkedList() {}
    void    add(const T &e);
    void    add(int index, const T &e);
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T &e);
    int     indexOf(const T &item);
    bool    contains(const T &item);
    string  toString();
    T       removeAt(const int index);
    T       removeItem(const T &item);
    Iterator begin() {
        return Iterator(this, true); }
    Iterator end() {
        return Iterator(this, false); }
public:
    class Node {
    private:
        T data;
        Node *next;
        Node *previous;
        friend class DLinkedList<T>;
        
        Iterator begin() {
            return Iterator(this, true);
        }
        Iterator end() {
            return Iterator(this, false);
        }

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
T DLinkedList<T>::removeAt(const int index) {
    /* Remove the element at given index from the list */
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
    else if (index == this->count - 1) {
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
        while (index > 1) {
            p = p->next;
            index--;
        }
        Node* q = p->next;
        p->next = q->next;
        q->next->previous = p;
        T data = q->data;
        delete q;
        this->count--;
        return data;
    }
}

template <class T>
T DLinkedList<T>::removeItem(const T& item) {
    /* Remove the first occurrence of item in the list */
    int index = this->indexOf(item);
    if (index == -1) throw std::out_of_range("Index out of range");
    T data = this->removeAt(index);
    return data;s
}


/*
-------------------------------------------------------------------------
--------------------------------INTERATOR--------------------------------
-------------------------------------------------------------------------
*/


/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin) {
    this->pList = pList;
    if (begin) {
        if (pList != NULL) {
            this->current = pList->head;
            this->index = 0;
        } else {
            this->current = nullptr;
            this->index = -1;
        }
    } else {
        this->current = nullptr;
        if (pList != NULL) this->index = pList->size();
        else this->index = 0;
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator) {
    this->pList = iterator.pList;
    this->current = iterator.current;
    this->index = iterator.index;

    return *this;
}

template <class T> 
void DLinkedList<T>::Iterator::set(const T &e) {
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
    this->current->data = e;
}

template<class T>
T& DLinkedList<T>::Iterator::operator*() {
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
    return this->current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove() 
{
    /*
    * TODO: delete Node in pList which Node* current point to. 
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */

}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator) {
    return (this->current != iterator.current || this->index != iterator.index);
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++() {
    
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int) 
{
    
}




int main() {
    DLinkedList<int> list;
    int size = 10;
    for(int idx=0; idx < size; idx++){
        list.add(0, idx);
    }
    cout << list.toString() << endl;

    return 0;
}