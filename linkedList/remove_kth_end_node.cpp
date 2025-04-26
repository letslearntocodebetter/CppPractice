/*
We use a dummy node so both pointers start from the same reference point.
We move fast pointer n+1 steps ahead (not just n) because:

We start at dummy, not at head
We need slow to end up at the node BEFORE the one we want to delete

After the first loop, fast is n+1 nodes ahead of slow.
When fast reaches the end (nullptr), slow will be exactly at the node before the one we need to remove.
This approach works for all cases, including removing the head node.
*/


class Solution {
    public:
        ListNode* removeNthFromEnd(ListNode* head, int n) {
            // Create a dummy node to handle edge cases
            ListNode dummy(0);
            dummy.next = head;
            
            // Initialize two pointers
            ListNode* fast = &dummy;
            ListNode* slow = &dummy;
            
            // Move fast pointer n+1 steps ahead
            // We go n+1 steps (not just n) because:
            // 1. We start at dummy, not head
            // 2. We want slow to point to the node BEFORE the one to be deleted
            for (int i = 0; i <= n; i++) {
                // Handle invalid n (larger than list size)
                if (!fast) return head;
                fast = fast->next;
            }
            
            // At this point, fast is n+1 nodes ahead of slow
            // Both started at dummy, so fast is at the nth node from head
            
            // Move both pointers at the same pace until fast reaches end
            // This will position slow at the node just before the one to remove
            while (fast) {
                slow = slow->next;
                fast = fast->next;
            }
            
            // When fast reaches nullptr (end of list),
            // slow will be at the node just before the nth node from the end
            ListNode* toDelete = slow->next;
            slow->next = slow->next->next;
            delete toDelete;
            
            return dummy.next;
        }
    };