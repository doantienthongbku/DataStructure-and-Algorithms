#include <bits/stdc++.h>
using namespace std;


class LLNode {
    public:
        int val;
        LLNode* next;
        LLNode();
        LLNode(int val, LLNode* next);
};

int convertToInt(LLNode* head) {
    string num = "";
    while (head != NULL) {
        num += std::to_string(head->val);
        head = head->next;
    }
    std::reverse(num.begin(), num.end());
    return stoi(num);
}

LLNode* convertToLL(int num) {
    string num_str = std::to_string(num);
    std::reverse(num_str.begin(), num_str.end());
    if (num_str.length() == 0) return new LLNode();
    LLNode* head = new LLNode(num_str[0] - '0', NULL);
    LLNode* temp = head;
    int len = num_str.length();
    for (int i = 1; i < len; i++) {
        temp->next = new LLNode(num_str[i] - '0', NULL);
        temp = temp->next;
    }
    return head;
}

LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
    int num_l0 = convertToInt(l0);
    int num_l1 = convertToInt(l1);
    int sum = num_l0 + num_l1;

    return convertToLL(sum);
}

int main() {


    return 0;
}
