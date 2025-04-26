class Solution {
public:
    // Approach 1: No recursion, using a stack
    bool isPalindromeStack(ListNode* head) {
        if (!head || !head->next) return true;  // Empty or single node list is palindrome
        
        // Step 1: Create a stack to store the first half of the list
        std::stack<int> values;
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Push the first half of the list to stack
        // Fast pointer moves twice as fast as slow
        // When fast reaches end, slow will be at middle
        while (fast && fast->next) {
            values.push(slow->val);
            slow = slow->next;
            fast = fast->next->next;
        }
        
        bool isOddLength = fast != nullptr; 
        // If list has odd number of nodes, skip the middle node
        if (isOddLength) {
            slow = slow->next;
        }
        
        // Compare second half with the values in the stack (first half in reverse)
        while (slow) {
            if (slow->val != values.top()) return false;
            values.pop();
            slow = slow->next;
        }
        
        return true;
    }
   
 
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;  // Empty or single node list is palindrome
        
        // Step 1: Find the middle of the list using fast and slow pointers
        ListNode* slow = head;
        ListNode* fast = head;
        
        // Using the more common pattern: fast && fast->next
        while (fast && fast->next) {
            slow = slow->next;      // Move slow by 1
            fast = fast->next->next; // Move fast by 2
        }
        
        // Now slow points to the node just after the middle
        // If odd length list: slow is at first node of second half
        // If even length list: slow is also at first node of second half
        
        // Step 2: Reverse the second half of the list
        // No need to use slow->next here since slow is already at
        // the beginning of the second half
        ListNode* secondHalf = reverseList(slow);
        
        // Step 3: Compare the first half with the reversed second half
        ListNode* firstHalf = head;
        ListNode* secondHalfCopy = secondHalf; // Store for restoring later
        
        bool result = true;
        // For odd length, second half will be one node shorter than first half
        // For even length, both halves will have equal nodes
        while (secondHalf) {
            if (firstHalf->val != secondHalf->val) {
                result = false;
                break;
            }
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }
        
        // Step 4: Restore the list by reversing second half again (optional)
        // Calculate where the middle is (previous node to secondHalfCopy)
        ListNode* mid = head;
        while (mid->next != secondHalfCopy && mid->next) {
            mid = mid->next;
        }
        mid->next = reverseList(secondHalfCopy);
        
        return result;
    }
    
private:
    // Helper function to reverse a linked list
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        return prev;
    }
};
