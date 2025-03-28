If you're asked to find a maximum, minimum, or optimal solution.

1. Optimization problems: If you're asked to find a maximum, minimum, or optimal solution.
2. Overlapping subproblems: If you notice that the same subproblems are being solved multiple times.
3. Optimal substructure: If an optimal solution can be constructed from optimal solutions of its subproblems.
4. Choice at each step: If you need to make a decision at each step, and this decision affects future steps.
5. Questions about counting the number of ways to do something.

Problems involving sequences or grids where you need to consider multiple paths.
When you're asked to find "all possible ways" to do something.

function dp(dp_state, memo_dict) {
    // check if we have seen this dp_state
    if dp_state in memo_dict
        return memo_dict[dp_state]

    // base case (a case that we know the answer for already) such as dp_state is empty
    if dp_state is the base cases
        return things like 0 or null
    
    calculate dp(dp_state) from dp(other_state)
    
    save dp_state and the result into memo_dict
}

function answerToProblem(input) {
    return dp(start_state, empty_memo_dict)
}

function dp(int n) {
    // check the validiy
    arry should have n+1 elemement to initialize
    // fil the arry with base cases

    // fill the arry with rest of the cases

   return array[n];
}
function answerToProblem(input) {
    return dp(number)
}

--
Greedy:

1. Local optimal choice: If making the best choice at each step leads to the global optimal solution.
2. Problems involving sorting or selecting the maximum/minimum element repeatedly.
Scheduling or interval problems.
3. Problems where you can make decisions sequentially without reconsidering previous choices.
4. Problems where you're asked to minimize or maximize something and can do so by making the best choice at each step.
5. Problems involving resources that can be optimally allocated one at a time.

dditional Tips:

Problem statement: Look for keywords like "maximum", "minimum", "optimal" (could be either DP or Greedy), "number of ways" (often DP).
Constraints: If the input size is small (e.g., n ≤ 1000), it might be solvable with DP.
 Very large input sizes often hint at Greedy or other more efficient algorithms.
Try small examples: If you can solve small instances by making obvious best choices at each step, 
it might be Greedy. If you need to consider multiple possibilities, it's more likely DP.
Consider the decision space: If you need to consider all possible decisions at each step, it's likely DP.
 If you can confidently make a single "best" decision at each step, it might be Greedy.
Look at related problems: LeetCode often groups similar problems together. If you've solved related problems with DP or Greedy, this might be a hint.