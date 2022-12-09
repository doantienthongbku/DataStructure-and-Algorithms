#include <iostream>
using namespace std;


class PrinterQueue {
    // your attributes
    class Node {
    public:
        int priority;
        string fileName;
        Node() {}
        Node(int priority, string fileName) : priority(priority), fileName(fileName) {} 
    };
    int count;
    Node *items;
public:
    // your methods
    PrinterQueue() {
        items = new Node[100];
        count = 0;
    }

    void swapNode(Node *x, Node *y) {
        Node temp = *x;
        *x = *y;
        *y = temp;
    }

    void reheapUp(Node *elements, int N, int index) {
        int parent = (index - 1) / 2;
    
        if (elements[index].priority > elements[parent].priority) {
            swapNode(&elements[index], &elements[parent]);
            reheapUp(elements, N, parent);
        }
    }

    void reheapDown(Node *elements, int N, int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < N && elements[left].priority < elements[smallest].priority) smallest = left;
        if (right < N && elements[right].priority < elements[smallest].priority) smallest = right;
        if (smallest != index) {
            swapNode(&elements[index], &elements[smallest]);
            reheapDown(elements, N, smallest);
        }
    }

    int findIndex(Node item) {
        for (int i = 0; i < count; i++)
            if ((items[i].priority == item.priority) && (items[i].fileName == items[i].fileName))
                return i;
        return -1;
    }

    void removeFile(Node item){
        if (count == 0) return;
        if (count == 1) { count--; return; }
        int index = findIndex(item);
        items[index] = items[count - 1];
        count--;
        reheapDown(items, count, index);
    }

    void heapSort() {
        for (int i = count / 2 - 1; i >= 0; i--)  // from parent to root
            reheapDown(items, count, i);

        for (int i = count - 1; i > 0; i--) {
            swapNode(&items[0], &items[i]);
            reheapDown(items, i, 0);
        }
    }  
    
    void addNewRequest(int priority, string fileName) {
        // your code here
        Node newNode(priority, fileName);
        items[count] = newNode;
        reheapUp(items, count, count);
        count++;
    }

    void print() {
        // your code here
        // After some logic code, you have to print fileName with endline
        if (count <= 0) {
            cout << "No file to print" << endl;
            return;
        }
        heapSort();
        cout << items[0].fileName << endl;
        removeFile(items[0]);
    }
};

int main() {
    PrinterQueue* myPrinterQueue = new PrinterQueue();
    myPrinterQueue->addNewRequest(1, "hello.pdf");
    myPrinterQueue->print();
    myPrinterQueue->print();
    myPrinterQueue->print();

    return 0;
}