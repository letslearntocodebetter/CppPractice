// Sometimes we start current from head even with a dummy node,
// but it depends on the specific algorithm:

// 1. When we start from dummy: When we need to potentially insert before the current head.
// When you need to find the node before insertion point
// Cleaner for insertion/deletion operations
// Standard pattern in most textbooks

// 2. When we start from head: 
// When you want explicit tracking of previous node
// More intuitive for some people
// Good when you need both current and previous references

void addNode_HeapDummy(List*& head, int val) {
    List* dummyNode = new List(0);  
	// Heap allocation
    or 
	// List dummyNode(0);              // Stack allocation
    // dummyNode.next = head;
	dummyNode->next = head;
    
    List* prev = dummyNode;
    List* cur = head;
    
    while (cur != nullptr && cur->val < val) {
        prev = cur;
        cur = cur->next;
    }
    
    List* newNode = new List(val);
    newNode->next = cur;
    prev->next = newNode;
    
    head = dummyNode->next;
    delete dummyNode;          
}

// =============================================================================
void addNodeInSortedLL_WithDummy(List*& head, int val) {
    // Create dummy node to simplify edge case handling
    ListNode dummy(-1);  // Use a small value as dummy
    dummy.next = head;
    
    // Start from dummy node
    ListNode* current = &dummy;
    
    // Find the correct position to insert
    // Stop when next node is null OR next node's value >= val
    while (current->next != nullptr && current->next->val < val) {
        current = current->next;
    }
    
    // Create new node and insert it
    ListNode* newNode = new ListNode(val);
    newNode->next = current->next;  // Link new node to the rest of list
    current->next = newNode;        // Link previous node to new node
    
    // CRUCIAL: Update head pointer (in case we inserted at beginning)
    head = dummy.next;
}

// =============================================================================
// METHOD 2: WITHOUT DUMMY NODE (More Complex, Handle Edge Cases)
// =============================================================================
void addNodeInSortedLL_WithoutDummy(List*& head, int val) {
    ListNode* newNode = new ListNode(val);
    
    // CASE 1: Empty list OR insert at beginning
    if (head == nullptr || head->val >= val) {
        newNode->next = head;
        head = newNode;
        return;
    }
    
    // CASE 2: Insert in middle or end
    ListNode* current = head;
    
    // Find the node after which we should insert
    // Stop when next is null OR next node's value >= val
    while (current->next != nullptr && current->next->val < val) {
        current = current->next;
    }
    
    // Insert the new node after current
    newNode->next = current->next;
    current->next = newNode;
}
