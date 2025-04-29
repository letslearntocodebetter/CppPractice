class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);  // Dummy node before head
        dummy.next = head;
        ListNode* prev = &dummy;
        ListNode* cur = head; // Pointer to track current node

        // adding a dummy node as previous would help us to avoid checking the nullptr for the first node;
        
        while (cur && cur->next) {
            ListNode* first = cur;
            ListNode* second = cur->next;

            // Swapping nodes
            first->next = second->next;
            second->next = first;
            prev->next = second;

            // Move prev and cur to the next pair
            prev = first;
            cur = first->next;
        }
        return dummy.next;
    }