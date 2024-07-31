// Here we use the dummy node and see the count numbers
// have a dummy tail

class Solution {
public:
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        if (!head) return nullptr;

        unordered_map<int, int> count;
        ListNode* cur = head;
        while (cur) {
            count[cur->val]++;
            cur = cur->next;
        }

        ListNode dummy(0);  // Dummy node to simplify head handling
        ListNode* tail = &dummy;
        cur = head;

        while (cur) {
            if (count[cur->val] == 1) {
                tail->next = cur;
                tail = tail->next;
            }
            cur = cur->next;
        }
        tail->next = nullptr;  // Ensure the last node points to nullptr

        return dummy.next;  // Return the head of the new list
    }
};