#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template<class K, class V>
class BinaryTree {
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    //~BinaryTree() {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    //}

    class Node {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value){
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    // STUDENT ANSWER BEGIN
    // You can define other functions here to help you.
    int getHeightRec(Node* subRoot) {
        if (subRoot == 0) return 0;
        return max(getHeightRec(subRoot->pLeft), getHeightRec(subRoot->pRight)) + 1;
    }

    int getHeight() {
        // TODO: return height of the binary tree.
        return getHeightRec(this->root);
    }

    string orderRec(Node* subRoot, string mode) {
        stringstream output;
        if (subRoot == 0) return "";
        if (mode == "pre") {
            output << subRoot->value << " ";
            output << orderRec(subRoot->pLeft, mode);
            output << orderRec(subRoot->pRight, mode);
        }
        else if (mode == "in") {
            output << orderRec(subRoot->pLeft, mode);
            output << subRoot->value << " ";
            output << orderRec(subRoot->pRight, mode);
        }
        else if (mode == "post") {
            output << orderRec(subRoot->pLeft, mode);
            output << orderRec(subRoot->pRight, mode);
            output << subRoot->value << " ";
        }
        return output.str();
    }

    string preOrder() {
        // TODO: return the sequence of values of nodes in pre-order.
        return orderRec(this->root, "pre");
    }

    string inOrder() {
        // TODO: return the sequence of values of nodes in in-order.
        return orderRec(this->root, "in");
    }

    string postOrder() {
        // TODO: return the sequence of values of nodes in post-order.
        return orderRec(this->root, "post");
    }
    // STUDENT ANSWER END
};

int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4); // Add to root
    binaryTree.addNode("L", 3, 6); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node

    cout << binaryTree.getHeight() << endl;
    cout << binaryTree.preOrder() << endl;
    cout << binaryTree.inOrder() << endl;
    cout << binaryTree.postOrder() << endl;

    return 0;
}