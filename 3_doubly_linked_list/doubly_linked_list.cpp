#include "doubly_linked_list.h"


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
        result += std::to_string(p->data);
        if (p->next) result += " ";
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
    /* Remove element at index and return removed value */
    if (index < 0 || index >= count ) throw std::out_of_range("Out of range");
    T val;
    if (index == 0){
        if (count == 1){
            val = head->data;
            delete head;
            head = NULL;
            tail = NULL; }
        else {
            head->next->previous = NULL;
            val = head->data;
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    } else {
        Node* pre = NULL;
        Node* cur = head;
        for (int i = 0; i < index; i++){
            pre = cur;
            cur = cur->next;
        }
        val = cur->data;
        pre->next = cur->next;
        if (cur->next == NULL) tail = pre;
        else cur->next->previous = pre;
        delete cur;
    }
    count--;
    return val;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item) {
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int index = indexOf(item);
    if (index != -1) {
        removeAt(index);
        return true;
    } else return false;
}

template<class T>
void DLinkedList<T>::clear(){
    /* Remove all elements in list */
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
    }
    tail = NULL;
}

template <class T>
void DLinkedList<T>::reverse() {
    /* Reverse the list */
    if (this->count == 0) return;
    Node* p = this->head;
    while (p) {
        Node* q = p->next;
        p->next = p->previous;
        p->previous = q;
        p = q;
    }
    Node* q = this->head;
    this->head = this->tail;
    this->tail = q;
}

template <class T>
void DLinkedList<T>::sort() {
    /* Sort the list */
    if (this->count == 0) return;
    Node* p = this->head;
    while (p) {
        Node* q = p->next;
        while (q) {
            if (p->data > q->data) {
                T temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
            q = q->next;
        }
        p = p->next;
    }
}

/*
----------------------------------------------------------------------------------
-----------------------------------INTERATOR--------------------------------------
----------------------------------------------------------------------------------
*/


/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from SLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T> *pList, bool begin)
{
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
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator &iterator)
{
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;

}

template <class T>
void DLinkedList<T>::Iterator::set(const T &e)
{
    if (this->current == NULL) throw std::out_of_range("Segmentation fault!");
    this->current->data = e;

}

template<class T>
T& DLinkedList<T>::Iterator::operator*()
{
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

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator &iterator)
{
    return (this->current != iterator.current || this->index != iterator.index);
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++()
{
    if (this->index == this->pList->size()) throw std::out_of_range("Segmentation fault!");
    if (this->current == NULL) this->current = this->pList->head;
    else this->current = this->current->next;
    this->index++;
    return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
    if (this->index == this->pList->size()) throw std::out_of_range("Segmentation fault!");
    if (this->current == NULL) this->current = this->pList->head;
    else this->current = this->current->next;
    this->index++;
    return *this;
}

int main() {
    DLinkedList<int> list;
    int size = 10;
    for (int idx = 0; idx < size; idx++)
    {
        list.add(idx);
    }
    cout << list.toString() << endl;

    DLinkedList<int>::Iterator it = list.begin();
    for(; it != list.end(); it++)
    {
        it.remove();
    }
    cout << list.toString();
    cout << endl;

    return 0;
}