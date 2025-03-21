

// Given the head of a list, reverse the list and 
// return the head of reversed list
Node *reverseList(Node *head) {
    // Initialize three pointers: curr, prev and next
   Node * cur = head;
   Node * prev = nullptr;
   Node * next = nullptr;
  
  while (cur)
  {
    // save the next one so that we can go further
    next = cur->next;

    // change the link;
    cur->next = prev;

    // move forward;
    prev = cur;
    cur = next;
  }
  
  return prev;

}

//using stack

// Function to reverse the linked list
Node* reverseList(Node* head) {
    // Create a stack to store the nodes
    stack<Node*> s;
    Node* cur = head;
      // Push all nodes except the last node into stack
    while (cur->next != NULL) {
        s.push(cur);
        cur = cur->next;
    }
    // Make the last node as new head of the linked list
    head = cur;
      // Pop all the nodes and append to the linked list
    while (!s.empty()) {
        // append the top value of stack in list
        cur->next = s.top();
          // Pop the value from stack
        s.pop();
          // move to the next node in the list
        cur = cur->next;
    }
      // Update the next pointer of last node of stack to NULL
    temp->next = nullptr;
      return head;
}




// A Simpler Analogy

// You're standing on a staircase. Each step represents a node in the list. Instead of turning around and running back,
// you ask the person ahead of you to reverse the rest of the line, and when they’re done, you just flip your link to point backward.
// So you're not doing the whole job—just one simple operation: “Make the next node point to me, and I’ll stop pointing to it.”



// Recursion breaks down the list until it hits the end.
// Then as the call stack unwinds, each node:
// Makes the next node point back to it.
// Cuts its own forward link.
// The last node becomes the new head.


Node* reverseList(Node* head) {
    // Base case: if list is empty or only one node, return head
    if (head == nullptr || head->next == nullptr)
        return head;

    // Reverse everything after head
    Node* restReversed = reverseList(head->next);

    // After recursion: head->next is the last node of reversed list
    Node* tail = head->next;
    tail->next = head;   // Point it back to current head
    head->next = nullptr; // Cut original link

    return restReversed; // This is the new head of the whole reversed list
}




