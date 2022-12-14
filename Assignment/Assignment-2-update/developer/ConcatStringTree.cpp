#include "ConcatStringTree.h"


// static identifier-------------------------------------------------------------------------------
ConcatStringTree::Identity ConcatStringTree::id = ConcatStringTree::Identity();
// ReducedConcatStringTree::Identity ReducedConcatStringTree::id = ReducedConcatStringTree::Identity();
//-------------------------------------------------------------------------------------------------

bool approved(const string& query) {
	bool found = false;
	for (int i = 0; i < query.length(); i++) {
		if (query[i] != 'l' && query[i] != 'r') found = true;
	}
	return !(found);
}

// ============================================================================
// Identity class =============================================================
// ============================================================================

ConcatStringTree::Identity::Identity() {
	this->key = 1;
}
unsigned int ConcatStringTree::Identity::value() {
	return this->key;
}
void ConcatStringTree::Identity::update() {
	if (((this->key) + 1)> 10e7) throw overflow_error("Id is overflow!");
	key++;
}

// ============================================================================
// Node class =================================================================
// ============================================================================

ConcatStringTree::Node::Node() {
    this->leftLength = 0;
    this->length = 0;
    this->pLeft = nullptr;
    this->pRight = nullptr;
    this->data = nullptr;
    this->num_ref = 0;
    this->key = id.value();
    id.update();
}

ConcatStringTree::Node::Node(const ConcatStringTree::Node &r) {
    this->leftLength = r.leftLength;
    this->length = r.length;
    this->data = new char[this->length + 1];
    for (int i = 0; i < this->length; i++) this->data[i] = r.data[i];
    this->data[this->length] = '\0';
    this->pLeft = r.pLeft;
    this->pRight = r.pRight;
    this->key = id.value();
    this->num_ref = 1;
    id.update();
}

ConcatStringTree::Node::Node(const char* s) {
    this->leftLength = 0;
    this->length = 0;
    while (s[length] != '\0') this->length++;
    this->data = new char[this->length + 1];
    for (int i = 0; i < this->length; i++) this->data[i] = s[i];
    this->data[this->length] = '\0';
    this->pLeft = this->pRight = nullptr;
    this->key = id.value();
    this->num_ref = 1;
    id.update();
}

ConcatStringTree::Node::~Node() {
    if (this->pLeft->AVL.size() == 0) this->pLeft->~Node();
	if (this->data != nullptr) delete[] data;
	if (this->pRight->AVL.size() == 0) this->pRight->~Node();   // delete AVL Tree
}

int ConcatStringTree::Node::indexOfNode(char c) {
    for (int i = 0; i < this->length; i++) {
        if (this->data[i] == c) return i;
    }
    return -1;
}

string ConcatStringTree::Node::toStringNode() {
    stringstream stream;
    if (this->data == nullptr) stream << "";
    else stream << this->data;
    return stream.str();
}

string ConcatStringTree::Node::toStringPreOrderNode() {
    stringstream stream;
    stream << "(LL=" << this->leftLength << ",L=" << this->length << ",";
    if (this->data == nullptr) stream << "<NULL>)";
    else stream << "\"" << this->data << "\")";
    return stream.str();
}

ConcatStringTree::Node ConcatStringTree::Node::reverseNode() {
    Node reversedNode;
    reversedNode.length = this->length;
    reversedNode.leftLength = this->length - this->leftLength;

    if (this->data == nullptr) reversedNode.data = nullptr;
    else {
        reversedNode.data = new char[this->length];
        for (int i = 0; i < this->length; i++) 
            reversedNode.data[i] = this->data[this->length - 1 - i];
        reversedNode.data[this->length] = '\0';
    }

    if (pRight == nullptr) reversedNode.pLeft = nullptr;
    else reversedNode.pLeft = new Node(pRight->reverseNode());
    if (pLeft == nullptr) reversedNode.pRight = nullptr;
    else reversedNode.pRight = new Node(pLeft->reverseNode());

    return reversedNode;
}

ConcatStringTree::Node ConcatStringTree::Node::subStringNode(int from, int to) {
	ConcatStringTree::Node Tree;

	if (this->data != nullptr) {
		if (from >= 0 && from < this->length && to > 0 && to <= this->length) {
            // cout << "case 1" << endl;
			Tree.length = to - from;
			Tree.leftLength = 0;
			Tree.data = new char [to - from];
			for (int i = 0; i < Tree.length; i++) {
				(Tree.data)[i] = data[i + from];
			}
			(Tree.data)[Tree.length] = '\0';
            // cout << "case 1 - end" << endl;
		}
		else if (from < 0 && to > 0 && to <= this->length) {
            // cout << "case 2" << endl;
			Tree.length = to;
			Tree.leftLength = 0;
			Tree.data = new char[from];
			for (int i = 0; i < Tree.length; i++) {
				(Tree.data)[i] = data[i];
			}
			(Tree.data)[Tree.length] = '\0';
            // cout << "case 2 - end" << endl;
		}
		else if (from >= 0 && from < this->length && to > this->length) {
            // cout << "case 3" << endl;
			Tree.length = this->length - from;
			Tree.leftLength = 0;
			Tree.data = new char[Tree.length];
			for (int i = 0; i < Tree.length; i++) {
				(Tree.data)[i] = data[i+from];
			}
			(Tree.data)[Tree.length] = '\0';
            // cout << "case 3 - end" << endl;
		}
		else {
            // cout << "case 4" << endl;
			Tree.length = this->length;
			Tree.leftLength = 0;
			Tree.data = new char[this->length];
			for (int i = 0; i < Tree.length; i++) {
				(Tree.data)[i] = data[i];
			}
			(Tree.data)[Tree.length] = '\0';
            // cout << "case 4 - end" << endl;
		}

		return Tree;
	} 
    else {
        if (from < this->leftLength && to > this->leftLength) {
            // cout << "case A" << endl;
            Tree.length = to - from;
            Tree.leftLength = this->leftLength - from;
            Tree.data = nullptr;
            Tree.pLeft = new Node (this->pLeft->subStringNode(from, leftLength));
            Tree.pRight = new Node (this->pRight->subStringNode(0, to-leftLength));
            // cout << "case A - end" << endl;
        }
        else if (from < this->leftLength && to <= this->leftLength) {
            // cout << "case B" << endl;
            Tree.length = to - from;
            Tree.leftLength = to - from;
            Tree.data = nullptr;
            Tree.pLeft = new Node(this->pLeft->subStringNode(from, to));
            // cout << "case B - end" << endl;
        }
        else if (from >= this->leftLength && to > this->leftLength) {
            // cout << "case C" << endl;
            Tree.length = to - from;
            Tree.leftLength = 0;
            Tree.data = nullptr;
            Tree.pRight = new Node(this->pRight->subStringNode(from - leftLength, to-leftLength));
            // cout << "case C - end" << endl;
        }
    }

	return Tree;
}

// ============================================================================
// ConcatStringTree class =====================================================
// ============================================================================

ConcatStringTree::ConcatStringTree() { this->root = new Node(); }

ConcatStringTree::ConcatStringTree(const char* s) { this->root = new Node(s); this->root->AVL.insertAVL(this->root->key); }

ConcatStringTree::~ConcatStringTree() {
    this->root->AVL.remove(this->root->key);
	if (this->root->pLeft != nullptr) this->root->pLeft->AVL.remove(this->root->key);
	if (this->root->pRight != nullptr) this->root->pRight->AVL.remove(this->root->key);
}

int ConcatStringTree::length() const { return this->root->length; }

char ConcatStringTree::get(int index) {    
    if (index < 0 || index >= this->root->length) throw std::out_of_range("Index of string is invalid!");
    Node* curr = this->root;
    while (curr->data == nullptr) {
        if (index < curr->leftLength) curr = curr->pLeft;
        else {
            index -= curr->leftLength;
            curr = curr->pRight;
        }
    }
    return curr->data[index];
}

void ConcatStringTree::indexOfRec(Node* node, char c, int& index) {
    if (node->data != nullptr) {
        for (int i = 0; i < node->length; i++) {
            if (node->data[i] == c) return;
            index++;
        }
    }
    else {
        if (node->pLeft) indexOfRec(node->pLeft, c, index);
        if (node->pRight) indexOfRec(node->pRight, c, index);
    }
}

int ConcatStringTree::indexOf(char c) {
    int index = 0;
    indexOfRec(this->root, c, index);
    return (index >= this->length()) ? -1 : index;
}

string ConcatStringTree::traverseNLR(Node* node, bool only_str) const {
    if (node == nullptr) return "";
    stringstream stream;
    if (!only_str) {
        if (node == this->root) stream << this->root->toStringPreOrderNode();
        else{
            stream << ";";
            stream << node->toStringPreOrderNode();
        }
    } else {
        stream << node->toStringNode();
    }
    
    // then recur on left subtree
    stream << traverseNLR(node->pLeft, only_str);
    // now recur on right subtree 
    stream << traverseNLR(node->pRight, only_str);

    return stream.str();
}

string ConcatStringTree::toStringPreOrder() const {
    stringstream stream;
    stream << "ConcatStringTree[";
    stream << this->traverseNLR(this->root, false);
    stream << "]";
    
    return stream.str();
}

string ConcatStringTree::toString() const {
    stringstream stream;
    stream << "ConcatStringTree[\"";
    stream << this->traverseNLR(this->root, true);
    stream << "\"]";
    
    return stream.str();
}

ConcatStringTree ConcatStringTree::concat(const ConcatStringTree& otherS) const {
    ConcatStringTree newCST;

    // update root
    newCST.root->pLeft = this->root;
    newCST.root->pRight = otherS.root;
    newCST.root->leftLength = this->root->length;
    newCST.root->length = this->root->length + otherS.root->length;
    
    // update ParentsTree
    newCST.root->pLeft->AVL.insertAVL(newCST.root->key);
	newCST.root->pRight->AVL.insertAVL(newCST.root->key);
	newCST.root->AVL.insertAVL(newCST.root->key);

    return newCST;
}

// substring
ConcatStringTree ConcatStringTree::subString(int from, int to) const {
	if (from < 0 || from >= this->length() || to <= 0 || to >= this->length()) throw std::out_of_range("Index of string is invalid!");
	if (from >= to) throw std::logic_error("Invalid range!");

	ConcatStringTree final;
	Node* node = new Node(root->subStringNode(from, to));
	final.root = node;
    // update ParentsTree
    final.root->AVL.insertAVL(final.root->key);
	return final;
}

ConcatStringTree ConcatStringTree::reverse() const {
    ConcatStringTree final;
    Node* p = new Node(root->reverseNode());
    final.root = p;
    // update ParentsTree
    final.root->AVL.insertAVL(final.root->key);

    return final;
}

int ConcatStringTree::getParTreeSize(const string& query) const {
	if (!approved(query)) throw runtime_error("Invalid character of query");
	Node* cur = this->root;
	for (int i = 0; i < query.length(); i++) {
		if (query[i] == 'l') {
			if (cur->pLeft == nullptr) throw runtime_error("Invalid query: reaching NULL");
			else cur = cur->pLeft;
		}
		else {
			if (cur->pRight == nullptr) throw runtime_error("Invalid query: reaching NULL");
			else cur = cur->pRight;
		}
	}
	return cur->AVL.size();
}
// string 
string ConcatStringTree::getParTreeStringPreOrder(const string& query) const {
	if (!approved(query)) throw runtime_error("Invalid character of query");
	Node* cur = this->root;
	for (int i = 0; i < query.length(); i++) {
		if (query[i] == 'l') {
			if (cur->pLeft == nullptr) throw runtime_error("Invalid query: reaching NULL");
			else cur = cur->pLeft;
		}
		else {
			if (cur->pRight == nullptr) throw runtime_error("Invalid query: reaching NULL");
			else cur = cur->pRight;
		}
	}
	return cur->AVL.toStringPreOrder();
}


// ============================================================================
// ParentsTree pNode class ====================================================
// ============================================================================

ConcatStringTree::ParentsTree::pNode::pNode() : pLeft(nullptr), pRight(nullptr) {}

ConcatStringTree::ParentsTree::pNode::pNode(unsigned int value) : key(value), pLeft(nullptr), pRight(nullptr), balance(EH) {}

string ConcatStringTree::ParentsTree::pNode::toStringPreOrder() {
	stringstream sstr;
	sstr << "(id=" << this->key << ")";
	return sstr.str();
}

// ============================================================================
// ParentsTree class ==========================================================
// ============================================================================

// ============================HELLPER FUNCTION================================

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::rotL(pNode *node) {
    pNode* temp = node->pRight;
    node->pRight = temp->pLeft;
    temp->pLeft = node;
    return temp;
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::rotR(pNode *node) {
    pNode* temp = node->pLeft;
    node->pLeft = temp->pRight;
    temp->pRight = node;
    return temp;
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::balanceLeft(pNode *node, bool& taller) {
    pNode* left = node->pLeft;
    if (left->balance == -1) {
        node = rotR(node);
        node->balance = EH;
        node->pRight->balance = EH;
        taller = false;
    }
    else if (left->balance == RH) {
        pNode* r = left->pRight;
        if (!r) return node;
        if (r->balance == LH) {
            node->balance = RH;
            left->balance = EH;
        }
        else if (r->balance == EH) {
            left->balance = EH;
            node->balance = EH;
        }
        else {
            node->balance = EH;
            left->balance = LH;
        }
        r->balance = EH;
        node->pLeft = rotL(left);
        node = rotR(node);
        taller = false;
    }
    else {
        node = rotR(node);
        node->balance = RH;
        node->pRight->balance = LH;
        taller = false;
    }
    return node;
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::balanceRight(pNode *node, bool& taller) {
    pNode* right = node->pRight;
    if (right->balance == -1) {
        node = rotL(node);
        node->balance = EH;
        node->pRight->balance = EH;
        taller = false;
    }
    else if (right->balance == LH) {
        pNode* l = right->pLeft;

        if (!l) return node;
        if (l->balance == RH) {
            node->balance = LH;
            right->balance = EH;
        }
        else if (l->balance == EH) {
            right->balance = EH;
            node->balance = EH;
        }
        else {
            node->balance = EH;
            right->balance = RH;
        }
        l->balance = EH;

        node->pRight = rotR(right);
        node = rotL(node);
        taller = false;
    }
    else {
        node = rotL(node);
        node->balance = LH;
        node->pLeft->balance = RH;
        taller = false;
    }

    return node;
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::insertAVLRec(pNode* node, unsigned int value, bool &taller) {
	if (node == NULL) {
		node = new pNode(value);
		taller = 1;
		return node;
	}
	if (value < node->key) {
		node->pLeft = insertAVLRec(node->pLeft, value, taller);
		if (taller) {
			if (node->balance == BalanceFactor::LH) node = balanceLeft(node, taller);
			else if (node->balance == BalanceFactor::EH) node->balance = BalanceFactor::LH;
			else if (node->balance == BalanceFactor::RH) {
				node->balance = EH;
				taller = 0;
			}
		}
	}
	else {
		node->pRight = insertAVLRec(node->pRight, value, taller);
		if (taller) {
			if (node->balance == RH) node = balanceRight(node, taller);
			else if (node->balance == EH) node->balance = RH;
			else {
				node->balance = EH;
				taller = 0;
			}
		}
	}
	return node;
}

int ConcatStringTree::ParentsTree::getHeightRec(pNode* node) {
    if (node == NULL) return 0;
    int lh = this->getHeightRec(node->pLeft);
    int rh = this->getHeightRec(node->pRight);

    return (lh > rh ? lh : rh) + 1;
}

int ConcatStringTree::ParentsTree::getBalanceFactor(pNode* node) {
	if (node == nullptr) return 0;
	return getHeightRec(node->pRight) - getHeightRec(node->pLeft);
}


ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::LLRotation(pNode* node) {
	pNode* plNode = node->pLeft;
	pNode* plrNode = plNode->pRight;
	plNode->pRight = node;
	node->pLeft = plrNode;
	if (root == node) { root = plNode; }
	return plNode;
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::RRRotation(pNode* node) {
	pNode* prNode = node->pRight;
	pNode* prlNode = prNode->pLeft;
	prNode->pLeft = node;
	node->pRight = prlNode;
	if (root == node) { root = prNode; }
	return prNode;
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::LRRotation(pNode* node) {
	node->pLeft = RRRotation(node->pLeft);
	return LLRotation(node);
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::RLRotation(pNode* node) {
	node->pRight = LLRotation(node->pRight);
	return RRRotation(node);
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::minValueNode(pNode* node) {
	pNode* curr = node;
	while (curr && curr->pLeft != nullptr) { curr = curr->pLeft; }
	return curr;
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::maxValueNode(pNode* node) {
	pNode* curr = node;
	while (curr && curr->pRight != nullptr) { curr = curr->pRight; }
	return curr;
}

ConcatStringTree::ParentsTree::pNode* ConcatStringTree::ParentsTree::deleteNodeRec(pNode* node, unsigned int key) {
	if (!node) { return node; }
	if (node->key < key) {
		node->pRight = deleteNodeRec(node->pRight, key);
	}
	else if (node->key > key) {
		node->pLeft = deleteNodeRec(node->pLeft, key);
	}
	else if (node->key == key && node->pLeft == nullptr) {
		pNode* temp = node->pRight;
		free(node);
		return temp;
	}
	else if (node->key == key && node->pRight == nullptr) {
		pNode* temp = node->pLeft;
		free(node);
		return temp;
	}
	else if (node->key == key && node->pRight != nullptr && node->pLeft != nullptr) {
		pNode* temp = maxValueNode(node->pLeft);
		node->key = temp->key;
		node->pLeft = deleteNodeRec(node->pLeft, temp->key);
	} if (node == nullptr) { return node; }
	int bf = getBalanceFactor(node);
	//LL Rotation 
	if (bf < LH && getBalanceFactor(root->pLeft) <= EH) {
		return LLRotation(node);
	}
	//RR Rotation 
	if (bf > RH && getBalanceFactor(root->pLeft) >= EH) {
		return RRRotation(node);
	}
	//LR Rotation 
	if (bf < LH && getBalanceFactor(root->pLeft) < EH) {
		return LRRotation(node);
	}
	//RL Rotation 
	if (bf > RH && getBalanceFactor(root->pLeft) > EH) {
		return RLRotation(node);
	}
	return node;
}

string ConcatStringTree::ParentsTree::toStringPreOrderRec(pNode* node) const {
	string s = "";
	if (node == nullptr) return "";
	// Print data of node
	if (node == root) s += node->toStringPreOrder();
	else {
		s += ";";
		s += node->toStringPreOrder();
	}
	// Print data of left subtree
	s += toStringPreOrderRec(node->pLeft);
	// Print data of right subtree 
	s += toStringPreOrderRec(node->pRight);
	return s;
}

// =============================MAIN FUNCTION=================================

ConcatStringTree::ParentsTree::ParentsTree() {}

void ConcatStringTree::ParentsTree::insertAVL(unsigned int value) {
    bool taller = false;
    this->root = insertAVLRec(this->root, value, taller);
    this->count++;
}

void ConcatStringTree::ParentsTree::remove(const unsigned int& value) {
	this->root = deleteNodeRec(this->root, value);
	count--;
}

int ConcatStringTree::ParentsTree::size() const {
	return this->count;
}

string ConcatStringTree::ParentsTree::toStringPreOrder() const {
	stringstream ss;
	ss << "ParentsTree[";
	ss << toStringPreOrderRec(root);
	ss << "]";
	return ss.str();
}


// ============================================================================
// HashConfig class ===========================================================
// ============================================================================

HashConfig::HashConfig() {}

HashConfig::HashConfig(int p, double c1, double c2, double lambda, double alpha, int initSize) {
    this->p = p;
    this->c1 = c1;
    this->c2 = c2;
    this->lambda = lambda;
    this->alpha = alpha;
    this->initSize = initSize;
}

// ============================================================================
// LitStringHash class ========================================================
// ============================================================================


LitStringHash::LitStringHash(HashConfig & hashConfig) {
    this->config = hashConfig;
    this->count = 0;
    this->lastInsertedIndex = -1;
    this->items = (char**) calloc (config.initSize, sizeof(char*));
    for (int i = 0; i < config.initSize; i++)
        this->items[i] = NULL;
}

LitStringHash::~LitStringHash() { this->hashClear(); }

int LitStringHash::getLastInsertedIndex() const {
    return this->lastInsertedIndex;
}

string LitStringHash::toString() const {
    stringstream stream;
    stream << "LitStringHash[";
    for (int i = 0; i < config.initSize; i++) {
        string tmp;
        if (this->items[i] == NULL) tmp = "()";
        else {
            string itemData(this->items[i]);
            tmp = "(litS=\"" + itemData + "\")";
        }
        if (i < config.initSize - 1) tmp += ";";
        stream << tmp;
    }
    stream << "]";
    
    return stream.str();
}

// ------------- HELPER FUNCTION --------------

int LitStringHash::pow(int a, int b) const {
    int result = 1;
    for (int i = 0; i < b; i++) {
        result *= a;
    }
    return result;
}

bool LitStringHash::strCompare(char* s1, char* s2) {
    string ss1(s1);
    return ss1.compare(s2);
}

void LitStringHash::freeItem(char *item) const {
    // free(item->litString);
    free(item);
}

// -------------------------------------------

int LitStringHash::hashFunction(const char* key) const {
    int sum = (int)key[0];
    for (int i = 1; key[i] != '\0'; i++)
        sum += (int)key[i] + pow(config.p, i);
    
    return sum % this->config.initSize;
}

int LitStringHash::quadraticFunction(const char* key, int i) const {
    int index = (this->hashFunction(key) + (int)(this->config.c1 * i) + (int)(this->config.c2 * 
                this->pow(i, 2))) % this->config.initSize;

    return index;
}


void LitStringHash::hashInsert(const char* s) {
    int index = hashFunction(s);
    char *curr = this->items[index];
    if (curr == NULL) {
        // LitString *item = new LitString(s);
        char* item = (char*)s;
        this->items[index] = item;
        
        this->lastInsertedIndex = index;
        this->count++;
        
        this->rehashingTable();
    } else {
        int i = 1;
        while (curr != NULL) {
            index = quadraticFunction(s, i);
            curr = this->items[index];
            i++;
            if (i >= this->config.initSize) throw std::runtime_error("No possible slot");
        }
        // LitString *item = new LitString(s);
        char* item = (char*)s;
        this->items[index] = item;
        this->lastInsertedIndex = index;
        this->count++;
        this->rehashingTable();
    }
}

void LitStringHash::hashInsert(const char* s, char** listItems) {
    int index = hashFunction(s);
    char *curr = this->items[index];
    if (curr == NULL) {
        // LitString *item = new LitString(s);
        char* item = (char*)s;
        listItems[index] = item;
        this->lastInsertedIndex = index;
        this->count++;
        this->rehashingTable();
    } else {
        int i = 1;
        while (curr != NULL) {
            index = quadraticFunction(s, i);
            curr = listItems[index];
            i++;
            if (i >= this->config.initSize) throw std::runtime_error("No possible slot");
        }
        // LitString *item = new LitString(s);
        char* item = (char*)s;
        listItems[index] = item;
        this->lastInsertedIndex = index;
        this->count++;
        this->rehashingTable();
    }
}

int LitStringHash::hashSearch(const char* s) {
    int index = hashFunction(s);
    char *curr = this->items[index];
    if (curr == NULL) return -1;
    else {
        int i = 1;
        while (strCompare((char*)s, curr)) {
            index = quadraticFunction(s, i);
            curr = this->items[index];
            i++;
            if ((i >= this->config.initSize) || (curr != NULL)) return -1;
        }
        return index;
    }
}

bool LitStringHash::isEmpty() { return (this->count == 0); }

void LitStringHash::rehashingTable() {
    if ((this->count / config.initSize) < config.lambda) return;
    else {
        // resize config for hash table
        int oldSize = config.initSize;
        config.initSize = (int)(config.initSize * config.alpha);
        char *lastInsertedNode = this->items[this->lastInsertedIndex];

        // Rehashing
        char** newItems = (char**) calloc (config.initSize, sizeof(char*));
        for (int i = 0; i < oldSize; i++)
            this->hashInsert(this->items[i], newItems);
        
        // re-initialize parameters
        this->items = newItems;
        this->lastInsertedIndex = this->hashSearch(lastInsertedNode);
    }
}

bool LitStringHash::hashRemove(const char* s) {
    int index = this->hashSearch(s);
    if (index == -1) return false;
    else {
        this->items[index] = NULL;
        this->count--;
        return true;
    }
}

void LitStringHash::hashClear() {
    for (int i = 0; i < config.initSize; i++) {
        char *item = this->items[i];
        if (item != NULL) item = NULL;
    }

    free(this->items);
    lastInsertedIndex = -1;
}


// ============================================================================
// ReducedConcatStringTree class ==============================================
// ============================================================================

ReducedConcatStringTree::ReducedConcatStringTree() { this->root = new Node(); }

ReducedConcatStringTree::ReducedConcatStringTree(const char* s, LitStringHash* litStringHash) {
    this->litStringHash = litStringHash;
    int index = this->litStringHash->hashSearch(s);
    
    if (index == -1) {
        this->litStringHash->hashInsert(s);
        this->root = new Node(s);
    } else {
        this->root = new Node(this->litStringHash->items[index]);
    }
    this->root->num_ref++;
    this->root->AVL.insertAVL(this->root->key);
}

ReducedConcatStringTree::~ReducedConcatStringTree() {
    this->root->AVL.remove(this->root->key);
	if (this->root->pLeft != nullptr) this->root->pLeft->AVL.remove(this->root->key);
	if (this->root->pRight != nullptr) this->root->pRight->AVL.remove(this->root->key);
    if (this->litStringHash->isEmpty()) this->litStringHash->hashClear();
}

int ReducedConcatStringTree::length() const { return this->root->length; }

char ReducedConcatStringTree::get(int index) {
    if (index < 0 || index >= this->root->length) throw std::out_of_range("Index of string is invalid!");
    Node* curr = this->root;
    while (curr->data == nullptr) {
        if (index < curr->leftLength) curr = curr->pLeft;
        else {
            index -= curr->leftLength;
            curr = curr->pRight;
        }
    }
    return curr->data[index];
}

void ReducedConcatStringTree::indexOfRec(Node* node, char c, int& index) {
    if (node->data != nullptr) {
        for (int i = 0; i < node->length; i++) {
            if (node->data[i] == c) return;
            index++;
        }
    }
    else {
        if (node->pLeft) indexOfRec(node->pLeft, c, index);
        if (node->pRight) indexOfRec(node->pRight, c, index);
    }
}

int ReducedConcatStringTree::indexOf(char c) {
    int index = 0;
    indexOfRec(this->root, c, index);
    return (index >= this->length()) ? -1 : index;
}


string ReducedConcatStringTree::traverseNLR(Node* node, bool only_str) const {
    if (node == nullptr) return "";
    stringstream stream;
    if (!only_str) {
        if (node == this->root) stream << this->root->toStringPreOrderNode();
        else{
            stream << ",";
            stream << node->toStringPreOrderNode();
        }
    } else {
        stream << node->toStringNode();
    }
    
    //then recur on left subtree
    stream << traverseNLR(node->pLeft, only_str);
    //now recur on right subtree 
    stream << traverseNLR(node->pRight, only_str);

    return stream.str();
}

string ReducedConcatStringTree::toStringPreOrder() const {
    stringstream stream;
    stream << "ConcatStringTree[";
    stream << this->traverseNLR(this->root, false);
    stream << "]";
    
    return stream.str();
}

string ReducedConcatStringTree::toString() const {
    stringstream stream;
    stream << "ConcatStringTree[\"";
    stream << this->traverseNLR(this->root, true);
    stream << "\"]";
    
    return stream.str();
}


ReducedConcatStringTree ReducedConcatStringTree::concat(const ReducedConcatStringTree & otherS) const {
    ReducedConcatStringTree newCST;

    //update root
    newCST.root->pLeft = this->root;
    newCST.root->pRight = otherS.root;
    newCST.root->leftLength = this->root->length;
    newCST.root->length = this->root->length + otherS.root->length;
    
    // update litStringHash
    newCST.litStringHash = otherS.litStringHash;

    // update ParentsTree
    newCST.root->pLeft->AVL.insertAVL(newCST.root->key);
	newCST.root->pRight->AVL.insertAVL(newCST.root->key);
	newCST.root->AVL.insertAVL(newCST.root->key);

    return newCST;
}


int ReducedConcatStringTree::getParTreeSize(const string & query) const {
    if (!approved(query)) throw runtime_error("Invalid character of query");
	Node* cur = this->root;
	for (int i = 0; i < query.length(); i++) {
		if (query[i] == 'l') {
			if (cur->pLeft == nullptr) throw runtime_error("Invalid query: reaching NULL");
			else cur = cur->pLeft;
		}
		else {
			if (cur->pRight == nullptr) throw runtime_error("Invalid query: reaching NULL");
			else cur = cur->pRight;
		}
	}
	return cur->AVL.size();
}

string ReducedConcatStringTree::getParTreeStringPreOrder(const string & query) const {
	if (!approved(query)) throw runtime_error("Invalid character of query");
	Node* cur = this->root;
	for (int i = 0; i < query.length(); i++) {
		if (query[i] == 'l') {
			if (cur->pLeft == nullptr) throw runtime_error("Invalid query: reaching NULL");
			else cur = cur->pLeft;
		}
		else {
			if (cur->pRight == nullptr) throw runtime_error("Invalid query: reaching NULL");
			else cur = cur->pRight;
		}
	}
	return cur->AVL.toStringPreOrder();   
}
