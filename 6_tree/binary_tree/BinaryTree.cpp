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
    ~BinaryTree() {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
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
    void addNode(string posFromRoot, K key, V value) {
        if (posFromRoot == "") { this->root = new Node(key, value); return; }
        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++) {
            if (!walker) return;
            if (posFromRoot[i] == 'L') walker = walker->pLeft;
            if (posFromRoot[i] == 'R') walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L') walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R') walker->pRight = new Node(key, value);
    }
    // STUDENT ANSWER BEGIN
    int countTwoChildrenNodeRec(Node* subRoot) {
        if (subRoot == 0) return 0;
        return (subRoot->pLeft && subRoot->pRight) ? 1 + countTwoChildrenNodeRec(subRoot->pLeft) + 
            countTwoChildrenNodeRec(subRoot->pRight) : 0;
    }

    int countTwoChildrenNode(){
        /*count the number of nodes with two children*/
        return countTwoChildrenNodeRec(this->root);
    }
    
    int getHeightRec(Node *node) {
        if (!node) return 0;
        return max(getHeightRec(node->pLeft), getHeightRec(node->pRight)) + 1;
    }

    int getHeight() {
        return getHeightRec(root);
    }

    string orderRec(Node *node, string mode) {
        stringstream stream;
        if (!node) return "";
        if (mode == "pre") {
            stream << node->value << " ";
            stream << orderRec(node->pLeft, mode);
            stream << orderRec(node->pRight, mode);
        } else if (mode == "in") {
            stream << orderRec(node->pLeft, mode);
            stream << node->value << " ";
            stream << orderRec(node->pRight, mode);
        } else if (mode == "post") {
            stream << orderRec(node->pLeft, mode);
            stream << orderRec(node->pRight, mode);
            stream << node->value << " ";
        }

        return stream.str();
    }

    string preOrder() {
        return orderRec(this->root, "pre");
    }

    string inOrder() {
        return orderRec(this->root, "in");
    }

    string postOrder() {
        return orderRec(this->root, "post");
    }

    void sumOfLeafsRec(Node *node, int *sum) {
        if (!node->pLeft && !node->pRight) *sum = *sum + node->value;
        if (node->pLeft) sumOfLeafsRec(node->pLeft, sum);
        if (node->pRight) sumOfLeafsRec(node->pRight, sum);
    }


    int sumOfLeafs() {
        if (!root) return 0;
        int sum = 0;
        sumOfLeafsRec(root, &sum);
        return sum;
    }

    // STUDENT ANSWER END
};


int main() {
	
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);
    binaryTree.addNode("L", 3, 6);
    binaryTree.addNode("R", 5, 9);
    cout << binaryTree.sumOfLeafs();

    return 0;
}