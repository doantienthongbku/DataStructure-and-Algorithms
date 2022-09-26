#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList {
protected:
    struct CharALNode {
        const char* data;
        int sub_len;
        CharALNode* next;
        CharALNode(const char* a) : data(a), next(nullptr) {
            string tmp_str(a);
            sub_len = tmp_str.length();
        };
        CharALNode() : next(nullptr), sub_len(0) {};
    };

    CharALNode* head;
    CharALNode* tail;
    int len;
    
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

public:
    ConcatStringList(const char *);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList & otherS) const;
    ConcatStringList subString(int from, int to) const;
    // ConcatStringList reverse() const;
    // ~ConcatStringList();

public:
    class ReferencesList {
        // TODO: may provide some attributes

        public:
            int size() const;
            int refCountAt(int index) const;
            std::string refCountsString() const;
    };

    class DeleteStringList {
        // TODO: may provide some attributes

        public:
            int size() const;
            std::string totalRefCountsString() const;
    };
};

ConcatStringList::ConcatStringList(const char* str) {
    this->head = new CharALNode(str);
    this->tail = head;
    std::string tmp_str(str);
    this->len = tmp_str.length();
}

int ConcatStringList::length() const { return len; }

char ConcatStringList::get(int index) const {
    if (index < 0 || index >= len) throw out_of_range("Index of string is invalid!");
    return toString()[index];
}

int ConcatStringList::indexOf(char c) const {
    string out = toString();
    if (out.find(c) != string::npos)
        return out.find(c);
    else return -1;
}

string ConcatStringList::toString() const {
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
    ConcatStringList out("");
    out.head = this->head;
    out.tail = otherS.tail;
    out.len = otherS.length() + this->length();

    return out;
}

ConcatStringList ConcatStringList::subString(int from, int to) const {
    if (from < 0 || to >= this->len) throw out_of_range("Index of string is invalid");
    if (from >= to) throw logic_error("Invalid range");

    CharALNode* p = head;
    int new_len = to - from;
    while (from < p->sub_len) {
        from = from - p->sub_len;
        p = p->next;
    }
    ConcatStringList out(p->data + from - 1);

    return out;
}

// ConcatStringList ConcatStringList::reverse() const {

// }

// ConcatStringList::~ConcatStringList() {
//     while (head) {
//         CharALNode* p = head;
//         head = head->next;
//         delete p;
//     }
// }


#endif // __CONCAT_STRING_LIST_H__