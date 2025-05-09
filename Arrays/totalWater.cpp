#include <iostream>
#include <vector>
#include <stack>
using namespace std;


// this is a monotonic decresing stack.
// the moment, we encounter the higher bar,
// we start calculating the water trap till 
// the stack is empty means till we calculater
// entire water.
// int distance = i - left - 1; because we are excluding the left bar width

// Use a monotonic decreasing stack of indices to detect valleys.
// Water is trapped between a left and right boundary.
// For each popped bar, calculate the trapped water between current and previous.

int trap(vector<int>& height) {
    stack<int> st;  // stores indices
    int totalWater = 0;
    int n = height.size();

    for (int i = 0; i < n; ++i) {
        // Check for right boundary
        while (!st.empty() && height[i] > height[st.top()]) {
            int right = i; // this is the right boundry 
            int bottom = st.top(); st.pop();  // valley

            if (st.empty()) {
                break;  // no left boundary
            }
            
            int left = st.top();  // left boundary
            int distance = right - left - 1; //  Exclude both boundries. i == right boundry
            int bounded_height = min(height[right], height[left]) - height[bottom];
            totalWater += distance * bounded_height;
        }

        st.push(i);  // push current index
    }

    return totalWater;
}
