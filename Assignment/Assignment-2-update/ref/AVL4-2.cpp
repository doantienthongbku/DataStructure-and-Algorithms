#include <iostream>
#include <vector>
#include <math.h>
#include <functional>
#include <stack>
#include <list>
#include <queue>
using namespace std;
void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int& n)
{
    cout << n << " ";
}

enum BalanceFactor { LH = -1, EH = 0, RH = 1 };
template <typename K,typename V>
class AVLTree {
public:
    class Entry {
    public:
        K key;
        V value;
        Entry(K key, V value) : key(key), value(value) {}
    };
    class Node {
    public:
        Entry* entry;
        Node* left;
        Node* right;
        int balance;


        Node(Entry* entry = NULL, Node* left = NULL, Node* right = NULL) {
            this->entry = entry;
            this->left = left;
            this->right = right;
            this->balance = 0;
        }
    };

    Node* insert(Node* p, K key, V value, bool& taller) {
        if (!p) {
            taller = true;
            Entry* e = new Entry(key, value);
            p = new Node(e, nullptr, nullptr);
            return p;
        }
        else {
            if (p->entry->key == key) {
                cout << key; throw ("Duplicate key");
            }
            if (key < p->entry->key) {
                p->left = insert(p->left, key, value, taller);
                if (taller) {
                    if (p->balance == -1) p = BalanceLeft(p, taller);
                    else if (p->balance == 0) p->balance = -1;
                    else {
                        p->balance = 0;
                        taller = false;
                    }
                }
            }
            else {
                p->right = insert(p->right, key, value, taller);
                if (taller) {
                    if (p->balance == -1) {
                        p->balance = 0;
                        taller = false;
                    }
                    else if (p->balance == 0) p->balance = 1;
                    else {
                        p = BalanceRight(p, taller);
                    }
                }
            }
        }
        return p;
    }
    Node* BalanceLeft(Node*& p, bool& taller) {
        Node* l = p->left;
        if (l->balance == -1) {
            p = rotR(p);
            p->balance = 0;
            p->right->balance = 0;
            taller = false;
        }
        else if (l->balance == 1) {
            Node* r = l->right;
            if (!r) return p;
            if (r->balance == -1) {
                p->balance = 1;
                l->balance = 0;
            }
            else if (r->balance == 0) {
                l->balance = 0;
                p->balance = 0;
            }
            else {
                p->balance = 0;
                l->balance = -1;
            }
            r->balance = 0;
            p->left = rotL(l);
            p = rotR(p);
            taller = false;
        }
        else {
            p = rotR(p);
            p->balance = 1;
            p->right->balance = -1;
            taller = false;
        }
        return p;
    }
    Node* BalanceRight(Node*& p, bool& taller) {
        Node* r = p->right;
        if (r->balance == 1) {
            p = rotL(p);
            p->balance = 0;
            p->left->balance = 0;
            taller = false;
        }
        else if (r->balance == -1) {
            Node* l = r->left;

            if (l->balance == 1) {
                p->balance = -1;
                r->balance = 0;
            }
            else if (l->balance == 0) {
                r->balance = 0;
                p->balance = 0;
            }
            else {
                p->balance = 0;
                r->balance = 1;
            }
            l->balance = 0;

            p->right = rotR(r);
            p = rotL(p);
            taller = false;
        }
        else {
            p = rotL(p);
            p->balance = -1;
            p->left->balance = 1;
            taller = false;
        }
        return p;
    }
    Node* rotL(Node* p) {
        Node* temp = p->right;
        p->right = temp->left;
        temp->left = p;
        return temp;
    }
    Node* rotR(Node* p) {
        Node* temp = p->left;
        p->left = temp->right;
        temp->right = p;
        return temp;
    }

    Node* remove(Node* p, K key, bool& shorter) {
        if (!p) {
            shorter = false;

            throw ("Not found");
        }
        if (key < p->entry->key) {
            p->left = remove(p->left, key, shorter);
            if (!shorter) {
                if (p->balance == -1) p->balance = 0;
                else if (p->balance == 0) {
                    p->balance = 1;
                    shorter = true;
                }
                else p = BalanceRight(p, shorter);
            }
        }
        else if (key > p->entry->key) {
            p->right = remove(p->right, key, shorter);
            if (!shorter) {
                if (p->balance == 1) p->balance = 0;
                else if (p->balance == 0) {
                    p->balance = -1;
                    shorter = true;
                }
                else p = BalanceLeft(p, shorter);
            }
        }
        else {
            Node* temp = p;
            if (!p->right) {
                Node* pt = p->left;

                shorter = false;
                delete temp;
                return pt;
            }
            else if (!p->left) {
                Node* pt = p->right;

                shorter = false;
                delete temp;
                return pt;
            }
            else {
                Node* pt = p->left;
                while (pt->right) pt = pt->right;
                p->entry->key = pt->entry->key;
                p->entry->value = pt->entry->value;
                p->left = remove(p->left, pt->entry->key, shorter);
                if (!shorter) {
                    if (p->balance == -1) p->balance = 0;
                    else if (p->balance == 0) {
                        p->balance = 1;
                        shorter = true;
                    }
                    else p = BalanceRight(p, shorter);
                }
            }
        }
        return p;
    }
    V search(Node* p, K key) {
        if (!p) throw ("Not found");
        if (p->entry->key == key) return p->entry->value;
        else if (p->entry->key > key) return search(p->left, key);
        else return search(p->right, key);

    }
    void traverseNLR(void (*func)(K key, V value), Node* p) {

        if (!p) return;

        func(p->entry->key, p->entry->value);

        traverseNLR(func, p->left);
        traverseNLR(func, p->right);
    }
    void clear(Node*& p) {
        if (!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
    }

    int getHeightRec(Node* node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->left);
        int rh = this->getHeightRec(node->right);
        return (lh > rh ? lh : rh) + 1;
    }
    public:
        Node* root;

        AVLTree() : root(NULL) {};
        ~AVLTree() { this->clear(); };
        void add(K key, V value) {
            bool taller = false;
            try { root = insert(root, key, value, taller); }
            catch (const char* msg)
            {
                cerr << msg << endl;
            }
        }
        void add(Entry* entry) {
            bool taller = false;
            try { root = add(root, entry, taller); }
            catch (const char* msg)
            {
                cerr << msg << endl;
            }
        }
        void remove(K key) {
            bool shorter = false;

            try { root = remove(root, key, shorter); }
            catch (const char* msg)
            {
                cerr << msg << endl;
            }
        }
        V search(K key) {
            V m;
            try { m = search(root, key); }
            catch (const char* msg)
            {
                cerr << msg << endl;
                return V();
            }
            return m;
        }

        void traverseNLR(void (*func)(K key, V value)) {
            traverseNLR(func, root);
        }

        void clear() { clear(root); }


        int getHeight()
        {
            return this->getHeightRec(this->root);
        } // for printing the tree

        void printTreeStructure()
        {
            int height = this->getHeight();
            if (this->root == NULL)
            {
                cout << "NULL\n";
                return;
            }
            queue<Node*> q;
            q.push(root);
            Node* temp;
            int count = 0;
            int maxNode = 1;
            int level = 0;
            int space = pow(2, height);
            printNSpace(space / 2);
            while (!q.empty())
            {
                temp = q.front();
                q.pop();
                if (temp == NULL)
                {
                    cout << " ";
                    q.push(NULL);
                    q.push(NULL);
                }
                else
                {
                    cout << temp->entry->key;
                    q.push(temp->left);
                    q.push(temp->right);
                }
                printNSpace(space);
                count++;
                if (count == maxNode)
                {
                    cout << endl;
                    count = 0;
                    maxNode *= 2;
                    level++;
                    space /= 2;
                    printNSpace(space / 2);
                }
                if (level == height)
                    return;
            }
        }
};
    

int main() {
    AVLTree<int, int>* tree = new AVLTree<int, int>();
    int keys[] = { 28,79,36,11,50,14,89,26,40,71,22,5,12,27,64,63,52,82,77,85,35,42,34,4,93,58,3,30,70,41,24,98,46,33 };

    for (int i = 0; i < 34; i++) tree->add(keys[i], keys[i]);
    tree->printTreeStructure();
}