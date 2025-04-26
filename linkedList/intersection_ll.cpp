class Solution {
    public:
        // Detect cycle and return the entry point (or nullptr if no cycle)
        ListNode* detectCycle(ListNode* head) {
            if (!head || !head->next) return nullptr;
            
            ListNode* slow = head;
            ListNode* fast = head;
            
            // Phase 1: Find meeting point inside cycle (if any)
            // Exit condition: fast == nullptr OR fast->next == nullptr
            // This means we've reached the end of a non-cyclic list
            while (fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;
                if (slow == fast) break;  // Meeting point found inside cycle
            }
            
            // If we exited the loop because fast/fast->next became nullptr,
            // it means there is no cycle
            if (!fast || !fast->next) return nullptr;
            
            // Phase 2: Find cycle entry point
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            
            return slow;  // Cycle entry point
        }
        
        // Find intersection point of two non-cyclic lists
        ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
            if (!headA || !headB) return nullptr;
            
            // Find lengths of both lists
            int lenA = 0, lenB = 0;
            ListNode* currA = headA;
            ListNode* currB = headB;
            
            while (currA) {
                lenA++;
                currA = currA->next;
            }
            
            while (currB) {
                lenB++;
                currB = currB->next;
            }
            
            // Reset pointers to heads
            currA = headA;
            currB = headB;
            
            // Advance the pointer of the longer list by the difference in lengths
            // We use < (not <=) because we're moving forward by the difference
            // E.g., if lenA = 5, lenB = 3, we move currA forward by 2 nodes
            if (lenA > lenB) {
                for (int i = 0; i < lenA - lenB; i++) {  // Move lenA-lenB times
                    currA = currA->next;
                }
            } else {
                for (int i = 0; i < lenB - lenA; i++) {  // Move lenB-lenA times
                    currB = currB->next;
                }
            }
            
            // Now both pointers are equidistant from the end of their lists
            // Move both pointers until they meet or reach the end
            while (currA && currB) {
                if (currA == currB) return currA;  // Intersection found
                currA = currA->next;
                currB = currB->next;
            }
            
            return nullptr;  // No intersection
        }
        
        // Check if two cycle entry points are in the same cycle
        bool areInSameCycle(ListNode* cycleA, ListNode* cycleB) {
            // We need this function because two lists with cycles
            // can have different entry points to the same cycle
            
            // Start from cycleA and traverse the cycle
            // If we encounter cycleB, they share the same cycle
            ListNode* temp = cycleA;
            do {
                if (temp == cycleB) return true;
                temp = temp->next;
            } while (temp != cycleA);  // Stop when we come back to cycleA
            
            return false;  // cycleB was not found in cycleA's cycle
        }
       // version 2o or same cycle
        bool areInSameCycle(ListNode* cycleA, ListNode* cycleB) {
    // Check if cycleA and cycleB are the same node initially
    if (cycleA == cycleB) return true;
    
    // Start from the node after cycleA
    ListNode* curr = cycleA->next;
    
    // Traverse until we reach cycleA again
    while (curr != cycleA) {
        // If we find cycleB in the cycle, they share the same cycle
        if (curr == cycleB) return true;
        curr = curr->next;
    }
    
    return false;  // cycleB was not found in cycleA's cycle
}
        // Main function to check if lists overlap
        bool checkOverlap(ListNode* headA, ListNode* headB) {
            if (!headA || !headB) return false;
            
            // Detect cycles in both lists
            ListNode* cycleA = detectCycle(headA);
            ListNode* cycleB = detectCycle(headB);
            
            // Case 1: Both lists are cycle-free
            if (!cycleA && !cycleB) {
                return getIntersectionNode(headA, headB) != nullptr;
            }
            
            // Case 2: One list has a cycle, the other doesn't
            if ((!cycleA && cycleB) || (cycleA && !cycleB)) {
                return false;  // They cannot intersect
            }
            
            // Case 3: Both lists have cycles
            // Check if they share the same cycle
            return areInSameCycle(cycleA, cycleB);
        }
    };

    