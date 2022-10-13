#ifndef __CONCAT_STRING_LIST_H__
#define __CONCAT_STRING_LIST_H__

#include "main.h"

class ConcatStringList {
public:
    class ReferencesList; // forward declaration
    class DeleteStringList; // forward declaration
    class CharALNode;
    class RefNode;

public:
    static ReferencesList refList;
    static DeleteStringList delStrList;

    CharALNode* head;
    CharALNode* tail;
    int count;

public:
    ConcatStringList(const char *);
    ConcatStringList(CharALNode *head, CharALNode *tail);
    int length() const;
    char get(int index) const;
    int indexOf(char c) const;
    std::string toString() const;
    ConcatStringList concat(const ConcatStringList & otherS) const;
    ConcatStringList subString(int from, int to) const;
    ConcatStringList reverse() const;
    ~ConcatStringList();

    // HELPER FUNCTIONS
    int numNodes() const;
    std::string reverseStr(string str) const;

public:
    class CharALNode {
    public:
        const char* data;
        CharALNode* next;
        
        CharALNode() : next(nullptr) {}
        CharALNode(const char* a) : data(a), next(nullptr) {}
        CharALNode(const char* a, CharALNode* next) : data(a), next(next) {}

        int getStrLen() const {
            string tmp_str(this->data);
            return tmp_str.length();
        }
    };

    class RefNode {
    public:
        CharALNode* point;
        int num_ref;
        RefNode* next;

        RefNode() : point(nullptr), next(nullptr), num_ref(0) {}
        RefNode(CharALNode* point, int num_ref) : point(point), num_ref(num_ref), next(nullptr) {}
    };

    class DelNode {
    public:
        RefNode* point;
        DelNode* next;

        DelNode() : point(nullptr), next(nullptr) {}
        DelNode(RefNode* point) : point(point), next(nullptr) {}
    };

    class ReferencesList {
    public:
        RefNode *head_ref;
        RefNode *tail_ref;
        RefNode *sorted;
        int num_node;

        ReferencesList() : head_ref(nullptr), tail_ref(nullptr), num_node(0) {}
        int size() const;
        int refCountAt(int index) const;

        std::string refCountsString() const;
        bool isExistAt(CharALNode *node, int num_ref);
        void update(CharALNode *node, int num_ref);
        void sortLinkedList();
        // check if all num_ref is equal to 0, return true
        bool isAllZero() const;
        // if all num_ref is equal to 0, delete all nodes
        void deleteAllNode();

        RefNode* getNodeFromCharALNode(CharALNode *node);
    };

    class DeleteStringList {
    public:
        DelNode *head_del;
        DelNode *tail_del;
        int num_node;

        int size() const;
        std::string totalRefCountsString() const;
        bool isExistAt(CharALNode *node);
        void updateDel(CharALNode *node);
        /* if num_ref == 0, delete node in DeleteStringList*/
        void deleteNode();
    };
};


#endif // __CONCAT_STRING_LIST_H__