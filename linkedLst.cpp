#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <tuple>
#include <numeric>
#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {
    }

    ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode* next) : val(x), next(next) {
    }
};

class LinkedLst {
public:
    // 160. Intersection of Two Linked Lists
    // first match each lists length, then start from the beginning of the equal length to find intersection
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int la = 0, lb = 0;
        ListNode* na = headA;
        ListNode* nb = headB;
        while (na != nullptr) {
            la++;
            na = na->next;
        }
        while (nb != nullptr) {
            lb++;
            nb = nb->next;
        }
        int diff = la - lb;
        while (diff > 0) {
            headA = headA->next;
            diff--;
        }
        while (diff < 0) {
            headB = headB->next;
            diff++;
        }
        while (headA != headB && headA != nullptr) {
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }

    /*
     * 2074. Reverse Nodes in Even Length Groups
     * Start the linked list from the beginning and group them into 1, 2, 3, 4... nodes
     * reverse the nodes in the even-length groups.
     *
     * e.g.
     * h = 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8
     * ->  1 -> 3 -> 2 -> 4 -> 5 -> 6 -> 8 -> 7
     */
    ListNode* reverseEvenLengthGroups(ListNode* h) {
        vector<ListNode *> vec;
        ListNode* ans = h;  // the return value
        ListNode* last = h;  // last node of previous vector
        int cur = 1, groupId = 1;  // cur is current number of nodes to be added in this round, groupId is the total number of nodes should be added
        while (h != nullptr) {
            if (cur == 0) {
                if (vec.size() % 2 == 0) {
                    reverse(vec.begin(), vec.end());
                }
                for (auto& ln : vec) {
                    last->next = ln;
                    last = last->next;
                }
                last->next = h;

                vec.clear();
                groupId++;
                cur = groupId;
            }
            vec.push_back(h);
            h = h->next;
            cur--;
        }
        if (vec.size() % 2 == 0) {
            reverse(vec.begin(), vec.end());
        }
        for (auto& ln : vec) {
            last->next = ln;
            last = ln;
        }
        last->next = nullptr;
        return ans;
    }
};
