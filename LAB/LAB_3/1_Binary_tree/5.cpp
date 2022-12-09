#include<iostream>
#include<string>
#include<queue>
using namespace std;

template<class K, class V>
class BinaryTree {
public:
    class Node;

private:
    Node *root;

public:
    BinaryTree() : root(nullptr) {}
    //~BinaryTree() {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    //}

    class Node {
    private:
        K key;
        V value;
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };

    void addNode(string posFromRoot, K key, V value) {
        if(posFromRoot == "") {
            this->root = new Node(key, value);
            return;
        }

        Node* walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l-1; i++) {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if(posFromRoot[l-1] == 'L')
            walker->pLeft = new Node(key, value);
        if(posFromRoot[l-1] == 'R')
            walker->pRight = new Node(key, value);
    }

    // STUDENT ANSWER BEGIN
    // You can define other functions here to help you.
    void BFS() {
        if (root == 0) return;
        string s;
        queue<Node*> q;
        q.push(this->root);

        while (!q.empty()) {
            Node* node = q.front();
            q.pop();
            s += std::to_string(node->value) + " ";
            if (node->pLeft != NULL) q.push(node->pLeft);
            if (node->pRight != NULL) q.push(node->pRight);
        }
        cout << s;
    }
    // STUDENT ANSWER END
};

int main() {
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("",2, 4); // Add to root
    binaryTree.addNode("L",3, 6); // Add to root's left node
    binaryTree.addNode("R",5, 9); // Add to root's right node
    binaryTree.BFS();
    cout << endl;

    return 0;
}