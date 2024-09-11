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
