class Solution {
    public:
        int maxArea(vector<int>& height) {
            int left = 0;
            int right = height.size() -1;
            int max_area = 0;
            
            while (left < right) {
                int area = (right - left) * std::min(height[right], height[left]);
                max_area = std::max(area, max_area);
                if (height[left] <= height[right]) {
                    left++;
                } else {
                    right--;
                }
            }
            return max_area;
        }
    }; 