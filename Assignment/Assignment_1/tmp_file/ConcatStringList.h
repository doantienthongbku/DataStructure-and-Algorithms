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
        friend class ConcatStringList;
        
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
        RefNode* getNodeFromCharALNode(CharALNode *node){
            RefNode *p = head_ref;
            while (p != nullptr) {
                if (p->point == node) return p;
                p = p->next;
            }

            return nullptr;
        }

        // TODO: make a sort

        void insertionSort();
        void sortedInsert(RefNode* newnode);
    };

    class DeleteStringList {
    public:
        RefNode *head_del;
        RefNode *tail_del;
        int num_node;

        int size() const {
            return num_node;
        }
        std::string totalRefCountsString() const {
            if (num_node == 0) return "TotalRefCounts[]";
            string out = "TotalRefCounts[";
            RefNode *p = head_del;
            int index = 0;
            while (index < num_node) {
                out += std::to_string(p->num_ref);
                if (index != num_node - 1) out += ",";
                p = p->next;
                index++;
            }
            out += "]";

            return out;
        }

        bool isExistAt(CharALNode *node) {
            if (num_node == 0) return false;
            RefNode *p = head_del;
            int index = 0;
            while (p != nullptr) {
                if (p->point == node) {
                    p->num_ref--; return true;
                }
                p = p->next;
            }

            return false;
        }

        void updateDel(CharALNode *node) {
            if (!isExistAt(node)) {
                RefNode *newnode = refList.getNodeFromCharALNode(node);
                newnode->num_ref--;
                if (num_node == 0) {
                    head_del = newnode;
                    tail_del = newnode;
                } else {
                    tail_del->next = newnode;
                    tail_del = newnode;
                }
                num_node++;
            }
        }


        // void updateDel(RefNode *node) {
        //     if (!isExistAt(node)) {
        //         DelNode *newNode = new DelNode(node, 1);
        //         if (this->head_del == nullptr) 
        //             this->head_del = this->tail_del = newNode;
                    
        //         else {
        //             this->tail_del->next = newNode;
        //             this->tail_del = newNode;
        //         }
        //         this->num_node++;
        //     }
        // }

        // void deleteLL() {
        //     DelNode *p = head_del;
        //     while (p != nullptr) {
        //         if (p->num_del == 0) {
        //             DelNode *tmp = p;
        //             delete tmp;
        //         }
        //         p = p->next;
        //     }
        // }
    };
};


#endif // __CONCAT_STRING_LIST_H__