#include "ConcatStringList.h"

ConcatStringList::ReferencesList ConcatStringList::refList = ConcatStringList::ReferencesList();
ConcatStringList::DeleteStringList ConcatStringList::delStrList = ConcatStringList::DeleteStringList();

int ConcatStringList::numNodes() const {
    if (this->count == 0) return 0;

    CharALNode* p = head;
    int numNode = 0;
    while(p != nullptr) {
        numNode++;
        p = p->next;
    }

    return numNode;
}


string ConcatStringList::reverseStr(string str) const {
    string tmp = str;

    int len = str.length();
    int n=len-1;
    for(int i=0;i<(len/2);i++){
        swap(tmp[i], tmp[n]);
        n = n-1;
    }

    return tmp;
}

ConcatStringList::ConcatStringList(const char* str) {
    if (str == ""){
        this->head = this->tail = nullptr;
        this->count = 0;
    } else {
        this->head = new CharALNode(str);
        this->tail = this->head;
        this->count = this->head->getStrLen();

        refList.update(this->head, 2);
    }
}

ConcatStringList::ConcatStringList(CharALNode *head, CharALNode *tail) {
    (this->head) = head;
    (this->tail) = tail;
}

int ConcatStringList::length() const { return this->count; }

char ConcatStringList::get(int index) const {
    if (index < 0 || index >= this->count) throw out_of_range("Index of string is invalid!");
    return this->toString()[index];
}

int ConcatStringList::indexOf(char c) const {
    string out = toString();
    if (out.find(c) != string::npos)
        return out.find(c);
    else return -1;
}

string ConcatStringList::toString() const {
    if (this->count == 0) return "";
    string out = "";
    CharALNode* p = head;
    while (p) {
        string tmp_str(p->data);
        out += tmp_str;
        p = p->next;
    }

    return out;
}

ConcatStringList ConcatStringList::concat(const ConcatStringList & otherS) const {
    tail->next = otherS.head;
    ConcatStringList out(this->head, otherS.tail);
    out.count = otherS.length() + this->length();

    refList.update(out.head, 1);
    refList.update(out.tail, 1);

    return out;
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
    if (from < 0 || to >= this->count) throw out_of_range("Index of string is invalid");
    if (from >= to) throw logic_error("Invalid range");

    int new_len = to - from;

    CharALNode* p = head;
    while (p->getStrLen() < from) {
        p = p->next;
        from = from - p->getStrLen();
    }

    if (new_len <= p->getStrLen() - from) {

        char* sub_buff = new char[new_len + 1];
        for (int i = from; i < new_len; i++) {
            sub_buff[i] = p->data[i];
        } 
        sub_buff[from + new_len] = '\0';

        ConcatStringList out(sub_buff);
        refList.update(out.head, 2);

        return out;
    }

    else {
        ConcatStringList out(p->data + from); p = p->next;
        new_len = new_len - out.length();

        while (new_len > 0) {
            if (p->getStrLen() < new_len) {
                CharALNode* tmp = new CharALNode(p->data);
                out.tail->next = tmp;
                out.tail = tmp;
            } else {
                char* sub_buff = new char[new_len + 1];
                for (int i = 0; i < new_len; i++) {
                    sub_buff[i] = p->data[i];
                }
                sub_buff[new_len] = '\0';

                CharALNode* tmp = new CharALNode(sub_buff);
                out.tail->next = tmp;
                out.tail = tmp;
            }

            new_len = new_len - p->getStrLen();
            p = p->next;
        }

        refList.update(out.head, 1);
        refList.update(out.tail, 1);

        return out;
    }
}

ConcatStringList ConcatStringList::reverse() const {
    if (this->count == 0) { return ConcatStringList(""); }

    ConcatStringList out(""); int num_node = this->numNodes();
    
    CharALNode *current = this->head;
    string* elements = new string[num_node + 1];

    int idx = 0;
    while (current != nullptr) {
        string tmp(current->data);
        string str_tmp = this->reverseStr(tmp);

        elements[idx] = str_tmp;
        current = current->next; idx++;
    }

    for (int i = num_node - 1; i >= 0; i--) {
        const char* chr = elements[i].c_str();
        CharALNode* newNode = new CharALNode(chr);

        if (out.head == nullptr) {
            out.head = newNode;
            out.tail = newNode;
        } else {
            out.tail->next = newNode;
            out.tail = newNode;
        }
    }
    out.count = this->count;

    refList.update(out.head, 1);
    refList.update(out.tail, 1);

    return out;
}

ConcatStringList::~ConcatStringList() {
    delStrList.updateDel(this->head);
    delStrList.updateDel(this->tail);
}

int ConcatStringList::ReferencesList::size() const {
    return num_node;
}

int ConcatStringList::ReferencesList::refCountAt(int index) const {
    if (index <= 0 || index >= num_node) throw std::out_of_range("Index of references list is invalid!");

    RefNode *p =head_ref;
    while (index > 0) {
        p = p->next;
        index--;
    }

    return p->num_ref;
}

std::string ConcatStringList::ReferencesList::refCountsString() const {
    if (num_node == 0) return "RefCounts[]";
    string out = "RefCounts["; RefNode *p = head_ref; int index = 0;
    
    while (index < num_node) {
        out += std::to_string(p->num_ref);
        if (index != num_node - 1) out += ",";
        p = p->next;
        index++;
    }
    out += "]";

    return out;
}

bool ConcatStringList::ReferencesList::isExistAt(CharALNode *node, int num_ref) {
    if (num_node == 0) return false;
    RefNode *p = head_ref;
    int index = 0;
    while (p != nullptr) {
        if (p->point == node) {
            p->num_ref += num_ref; return true;
        }
        p = p->next;
    }

        return false;
}

void ConcatStringList::ReferencesList::update(CharALNode *node, int num_ref) {
    if (!isExistAt(node, num_ref)) {
        RefNode *newNode = new RefNode(node, num_ref);
        if (this->head_ref == nullptr) 
            this->head_ref = this->tail_ref = newNode;
            
        else {
            this->tail_ref->next = newNode;
            this->tail_ref = newNode;
        }
        this->num_node++;
    }

    // insertionSort();
}


void ConcatStringList::ReferencesList::insertionSort() {
    sorted = nullptr;
    RefNode *current = this->head_ref;

    while (current != nullptr)
    {
        RefNode* next = current->next;
        sortedInsert(current);
        current = next;
    }

    this->head_ref = sorted;
}

void ConcatStringList::ReferencesList::sortedInsert(RefNode* newnode) {
    if (sorted == nullptr || sorted->num_ref >= newnode->num_ref) {
        newnode->next = sorted;
        sorted = newnode;
    }
    else {
        RefNode* current = sorted;
        while (current->next != nullptr &&
            current->next->num_ref < newnode->num_ref)
        {
            current = current->next;
        }
        newnode->next = current->next;
        current->next = newnode;
    }
}


