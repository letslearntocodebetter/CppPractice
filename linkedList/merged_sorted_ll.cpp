/**
Create a dummy node to simplify head tracking
Use a tail pointer to track where to attach the next node
Compare nodes from both lists, attach the smaller one to tail
Advance the pointer for the list we took a node from
Continue until one list is exhausted
Attach any remaining nodes from the non-empty list
Return dummy.next as our result head* Definition for singly-linked list.

Why use a dummy node? The dummy node approach simplifies the code by eliminating the need
for special cases to handle the first node.Without a dummy node, we'd need separate logic
to initialize the head of the result list and then to append subsequent nodes.
 */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // Create a dummy node to simplify handling the head
        ListNode dummy(0);
        // Tail tracks where to attach the next node
        ListNode* tail = &dummy;
        
        // Process both lists until at least one is empty
        while (list1 && list2) {
            // Compare current nodes and attach the smaller one
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            // Advance tail pointer
            tail = tail->next;
        }
        
        // Attach any remaining nodes from non-empty list
        tail->next = list1 ? list1 : list2;
        
        // Return the head of merged list (skip the dummy)
        return dummy.next;
    }
};