# Monotonic Stacks: Applications and Problem Patterns

Monotonic stacks are powerful data structures that maintain elements in either non-increasing or non-decreasing order. They're particularly useful for problems that involve finding the next greater/smaller element or when you need to maintain a view of relative ordering in a sequence. Here's a comprehensive guide to when and how to use them:

## Key Situations for Using Monotonic Stacks

### 1. Next Greater/Smaller Element Problems
Monotonic stacks excel at efficiently finding the next greater or smaller element for each element in an array.

**Signs to look for:**
- You need to find the next greater/smaller element for each element in an array
- You need to find the nearest greater/smaller element to the left/right

**Example problems:**
- Next Greater Element I/II
- Daily Temperatures (find days until warmer temperature)
- Stock Span Problem (consecutive days with price less than or equal to today)

### 2. Histogram-based Problems
When dealing with calculating areas, volumes, or ranges based on heights.

**Signs to look for:**
- Problems involving calculation with "heights" or "elevations"
- Problems asking about largest rectangles or areas
- Water trapping problems

**Example problems:**
- Largest Rectangle in Histogram
- Trapping Rain Water (as we solved earlier)
- Container With Most Water (variation)

### 3. Subarray Problems with Min/Max Constraints
Finding subarrays that satisfy certain min/max conditions.

**Signs to look for:**
- Problems asking about subarrays with constraints on min/max elements
- Problems about ranges where some property holds

**Example problems:**
- Sum of Subarray Minimums/Maximums
- Maximum Subarray Min-Product

### 4. Circular Array Problems
Problems that require a view of the entire array as a circular structure.

**Signs to look for:**
- Problems explicitly mentioning circular arrays
- Problems where you need to wrap around from end to beginning

**Example problems:**
- Next Greater Element II (circular array)
- Sum of Subarray Ranges (with circular extension)

## How to Recognize When to Use Monotonic Stacks

1. **Look for comparison patterns**: If the problem involves comparing elements and finding relationships like "next greater" or "previous smaller", a monotonic stack might be applicable.

2. **Check for O(n) requirements**: If a brute force approach would be O(n²) but an O(n) solution seems possible, consider a monotonic stack.

3. **Identify "nearest" or "next" in the problem**: Keywords like "nearest", "next", "closest" often hint at monotonic stack solutions.

4. **Look for histogram-like computations**: If you're calculating areas based on heights or evaluating ranges based on values, monotonic stacks are useful.

## Implementation Pattern

A typical monotonic stack implementation follows this pattern:

```cpp
// For a non-increasing monotonic stack (finding next greater element)
stack<int> st;
for (int i = 0; i < n; i++) {
    // While current element breaks monotonicity
    while (!st.empty() && arr[st.top()] < arr[i]) {
        int top = st.top();
        st.pop();
        
        // Process the popped element
        // This is where you compute your result
        result[top] = i - top; // or some other calculation
    }
    
    // Push current element index
    st.push(i);
}

// Process remaining elements in stack if needed
while (!st.empty()) {
    int top = st.top();
    st.pop();
    // Handle elements that don't have a "next greater"
    result[top] = -1; // or some default value
}
```

## Examples of Processing Logic

The core difference in monotonic stack problems is in how you process elements when they're popped from the stack:

1. **Next Greater Element**: When an element is popped, the current element is its next greater element.

2. **Trapping Rain Water**: Calculate water above the popped element based on boundaries.

3. **Largest Rectangle**: When an element is popped, calculate rectangle with the popped element's height.

4. **Sum of Subarray Minimums**: When popping, calculate how many subarrays have this element as the minimum.

## Choosing Between Increasing vs. Decreasing Stacks

- Use a **non-decreasing stack** (each element ≥ previous) when finding the next smaller element.
- Use a **non-increasing stack** (each element ≤ previous) when finding the next greater element.

The choice depends on the problem requirements and what relationship you're trying to identify.

---

By understanding these patterns, you'll be able to identify when a monotonic stack is the right tool for a problem and implement an efficient solution. The key insight is recognizing when a problem requires maintaining a view of elements in a specific order while processing a sequence.