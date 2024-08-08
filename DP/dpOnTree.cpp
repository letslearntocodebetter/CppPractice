Go to a node in then
base condition and left answer, right answer and then get the answer

Hypothesis is always correct


induction step - use hypothesis to get the base condition

int solve(node* node, int & result) {
    // base condition is always
    if (node == nullptr) { retuslt 0 return result}

    // solve left and right answers
    left = solve(node->left, result)
    right = solve(node->right,result)

    //calculate anwer for node
    result = `node + left + right

    
    return result;

}