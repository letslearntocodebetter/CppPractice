// monotonic stack

// The key idea behind monotonic stack problems is to use the stack to keep track of elements that have not yet found 
// their desired smaller or larger element. As we iterate through the elements o
// f the sequence, we can efficiently find the nearest smaller or larger element by comparing the current element with the elements present in the stack.

vector<int> dailyTemperatures(vector<int> temp) 
{
  vector<int> ans(temperatures.size());
  stack<pair<int, int>> s;

  for (int i=1; i < tmp.size(); i++) {
       while (!s.empty() && s.top().first <= tmp[i] {
          auto index = s.top().second;
          ans[index] = i - index;
          s.pop();
      }
      // push the greatest element on the top
      s.emplace(tmp[i], i);
  }
  ret ans;
}

def monotonic(something):
    stack = []
    for i in range(len(something)):
        while stack and stack[-1] >= something[i]: # '>=' can be substitute for any operation reqd
            curr = stack.pop()
            # this where you do something with curr
        if stack:
            # this is where you do something if the stack isn't empty - NOT ALWAYS REQD
            pass
        stack.append(something[i]) # append current index's item to stac


  // Buildings With an Ocean View
class Solution:
    def findBuildings(self, heights: List[int]) -> List[int]:
        stack = []
        for i in range(len(heights)):
            while stack and heights[stack[-1]] <= heights[i]:
                stack.pop()
            stack.append(i)
        return stack



//  1944. Number of Visible People in a Queue
