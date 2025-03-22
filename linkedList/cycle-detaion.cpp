class Solution {
    public:
        bool hasCycle(ListNode *head) {
            if (head == nullptr || head->next == nullptr) {
                return false; // No cycle if the list is empty or has only one node
            }
    
            ListNode *slow = head;
            ListNode *fast = head;
    
            while (fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;
    
                if (slow == fast) {  // Cycle detected
                    // Step 2: Find the start of the cycle
                    slow = head;     // Move slow back to head
                    
                    while (slow != fast) { // Move both at same pace
                        slow = slow->next;
                        fast = fast->next;
                    }
                    
                    return slow;  // Cycle start node

                }
            }
    
            return nullptr; // No cycle found
        }
    };
    

    // other loop


        // Find the meeting point of the slow and fast pointers
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break; // Meeting point found!
            }
        }

        // If there is no meeting point, there is no cycle
        if (fast == nullptr || fast->next == nullptr) {
            return nullptr;
        }

        // Find the start of the cycle
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
         return slow; \\


         //This mathematical insight is what allows us to use Floyd’s Cycle Detection Algorithm to detect the cycle and find the exact starting 
         // point of the cycle efficiently. By using the fact that the distance from the head to the start of the cycle is the same as the distance from the mee
         // ting point to the cycle start, we can find the starting node in just one more iteration after detecting the cycle.