
class Solution {
public:
    Node* copyRandomList(Node* head) {
        // Edge case: empty list
        if (!head) return nullptr;
        
        // HashMap to store mapping from original nodes to their copies
        unordered_map<Node*, Node*> nodeMap;
        
        // First pass: Create a copy of each node and store in the hash map
        Node* current = head;
        while (current) {
            // Create a new node with the same value
            nodeMap[current] = new Node(current->val);
            current = current->next;
        }
        
        // Second pass: Assign next and random pointers for the copied nodes
        current = head;
        while (current) {
            // Get the corresponding copy node
            Node* copy = nodeMap[current];
            
            // Assign next pointer - points to the copy of the original's next
            copy->next = nodeMap[current->next]; // Will be nullptr if current->next is nullptr
            
            // Assign random pointer - points to the copy of the original's random
            copy->random = current->random ? nodeMap[current->random] : nullptr;
            
            // Move to the next node in the original list
            current = current->next;
        }
        
        // Return the head of the copied list
        return nodeMap[head];
    }
};
