class Solution {
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
            // Create a dummy node to simplify handling the result list
            ListNode dummy(0);
            ListNode* tail = &dummy;
            
            int carry = 0;  // To store carry forward value
            
            // Process both lists until both are exhausted and no carry remains
            while (l1 || l2 || carry) {
                // Get values from current nodes (0 if node is null)
                int val1 = l1 ? l1->val : 0;
                int val2 = l2 ? l2->val : 0;
                
                // Compute sum and new carry
                int sum = val1 + val2 + carry;
                carry = sum / 10;  // Integer division gives carry
                
                // Create new node with the digit (sum % 10)
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
                
                // Move to next nodes if available
                if (l1) l1 = l1->next;
                if (l2) l2 = l2->next;
            }
            
            // Return head of result list (skip dummy node)
            return dummy.next;
        }
    };