#include <iostream>
#include <string>
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
    virtual string toString() = 0;
};

template <class T>
class DenseArray : public BaseList<T> {
protected:
    T *data;
    int capacity;
    int count;
public:
    DenseArray();
    virtual ~DenseArray();
    virtual void add(T element);
    virtual void add(int index, T element);
    virtual T removeAt(int index) = 0;
    virtual bool removeItem ( T item );
    virtual bool empty ();
    virtual int size ();
    virtual void clear ();
    virtual T get ( int index );
    virtual void set ( int index , T element );
    virtual int indexOf ( T item );
    virtual bool contains ( T item );
    virtual string toString ();
    virtual void dump ();
private :
    void checkIndex (int index );
    void ensureCapacity ( int capacity );
};

template <class T>
void DenseArray<T>::checkIndex(int index) {
    if (index < 0 || index >= this->count) throw std::out_of_range("Index out of range");
}

template <class T>
void DenseArray<T>::ensureCapacity(int capacity) {
    if (capacity > this->capacity) {
        int newCapacity = this->capacity * 3 / 2;
        if (newCapacity < capacity) newCapacity = capacity;
        T *newData = new T[newCapacity];
        memmove(newData, this->data, this->count + sizeof(T));
        this->capacity = newCapacity;
        delete[] this->data;

        this->data = newData; 
    }
}

template <class T>
DenseArray<T>::DenseArray() {
    this->capacity = 10;
    this->data = new T[this->capacity];
    this->count = 0;
}

template <class T>
DenseArray<T>::~DenseArray() {
    delete[] this->data;
}

template <class T>
void DenseArray<T>::add(T element) {
    this->ensureCapacity(this->count + 1);

    this->data[this->count] = element;
    this->count++;
}

template <class T>
void DenseArray<T>::add(int index, T element) {
    this->checkIndex(index);
    this->ensureCapacity(this->count + 1);
    
    int moveCount = this->count - index;
    if (moveCount > 0)
        memmove(this->data + index + 1, this->data + index, moveCount * sizeof(T));
    
    this->data[index] = element;
    this->count++;
}

template <class T>
T DenseArray<T>::removeAt(int index) {
    this->checkIndex(index);
    T dataRemoved = this->data[index];

    int moveCount = this->count - index - 1;
    if (moveCount > 0)
        memmove(this->data + index, this->data + index + 1, moveCount * sizeof(T));
    
    this->count--;
    return dataRemoved;
}

template <class T>
bool DenseArray<T>::removeItem(T item) {
    for (int i = 0; i < this->count; i++)
        if (this->data[i] == item) {
            removeAt(i);
            return true;
        }
    
    return false;
}

template <class T>
bool DenseArray<T>::empty() {
    return (this->count == 0);
}

template <class T>
int DenseArray<T>::size() {
    return this->count;
}

template <class T>
void DenseArray<T>::clear() {   // delete all data and reset
    delete[] this->data;

    this->capacity = 10;
    this->data = new T[this->capacity];
    this->count = 0;
}

template <class T>
T DenseArray<T>::get(int index) {
    this->checkIndex(index);
    return this->data[index];
}

template <class T>
void DenseArray<T>::set(int index, T element) {
    this->checkIndex(index);
    this->data[index] = element;
}

template <class T>
int DenseArray<T>::indexOf(T element) {
    for (int i = 0; i < this->count; i++)
        if (this->data[i] == element)
            return i;
    return -1;
}

template <class T>
bool DenseArray<T>::contains(T element) {
    return this->indexOf(element) != -1;
}

template <class T>
void DenseArray<T>:: dump () {
    string line (50 , '=');
    cout << line << endl ;
    cout << " Integer list 's information :" << endl ;
    cout << "- Capacity : " << this -> capacity << endl ;
    cout << "- Size : " << this -> count << endl ;
    cout << "- Data : " << this -> toString () << endl ;
    cout << line << endl ;
}


int main() {


    return 0;
}