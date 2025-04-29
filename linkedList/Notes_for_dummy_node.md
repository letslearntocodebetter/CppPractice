1. When the head might change
If your operation can modify the first node of the list
Examples: swapping nodes, removing duplicates, merging lists

2. When building a new list
If you're creating a new list from scratch or by selective filtering
Examples: adding numbers, merging lists, removing duplicates by value

3.To unify the code path
To avoid special-case handling for the first node
Makes code cleaner and less error-prone

3.When you need a reference to "before the list"

Operations that need to insert before the current head
Or need to track a "previous" pointer from the very start


4.For operations that require "look ahead" logic

When you need to make decisions based on the next node
The dummy node provides a consistent starting point
The key insight is that dummy nodes eliminate edge cases by providing a consistent anchor point before the actual list starts, eliminating the need for special handling of the first node.




1. When to use dummy node

To make sure the addition of a new node does not need extra check then it is better to use dummy node 

Exmaple:

addNode(list *head, value) {
    newNode = new Node(value);
    list dummyNode;
    dummyNode.next = head;
    
    currentNode = &dummyNode;
    while(current->next) {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;

    return dummyNode.next; or head;
}
// without dummy node

addNode(list *head, value) {
    newNode = new Node(value);
    if (head == nullptr) {
        head = newNode;
    } else {
        cur = head;
        while(cur->next) {
            cur = cur->next;
        }
        cur->next = newNode; 
    }
}



addNode(& *head, & *tail) {
    auto newNode = new Node;

    if (head == nullptr) {
        tail = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;

}

Actual code:

void addNode(ListNode*& head, int value) {
    // Create a dummy node
    ListNode dummy(0);  // Dummy node with an arbitrary value
    dummy.next = head;  // Link dummy node to the current head

    // Initialize current to the dummy node
    ListNode* current = &dummy;

    // Traverse to the end of the list
    while (current->next != nullptr) {
        current = current->next;
    }

    // Create and add the new node at the end
    ListNode* newNode = new ListNode(value);
    current->next = newNode;

    // Update the head to the next node of the dummy
    head = dummy.next;

}



void addNode(ListNode*& head, int value) {
    // Create the new node with the provided value
    ListNode* newNode = new ListNode(value);
    
    // If the list is empty, the new node becomes the head
    if (head == nullptr) {
        head = newNode;
    } else {
        // Otherwise, traverse to the end of the list
        ListNode* cur = head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        // Attach the new node at the end
        cur->next = newNode;
    }
}


void addNodeSorted(ListNode*& head, int value) {
    // Create a dummy node to simplify head handling
    ListNode dummy(0);
    dummy.next = head;
    
    // Find the position to insert
    ListNode* current = &dummy;
    while (current->next && current->next->val < value) {
        current = current->next;
    }
    
    // Insert the new node
    ListNode* newNode = new ListNode(value);
    newNode->next = current->next;
    current->next = newNode;
    
    // Update head (necessary because head might change)
    head = dummy.next;
}