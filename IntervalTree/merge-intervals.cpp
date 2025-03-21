class Solution {
    public:
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            // Sort intervals by start time
            std::sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
                return a[0] < b[0]; 
            });
            
            std::vector<vector<int>> results;
            results.push_back(intervals[0]);
            
            for (int i = 1; i < intervals.size(); ++i) {
                // If current interval overlaps with the last result
                if (results.back()[1] >= intervals[i][0]) {
                    // Merge by updating the end time
                    results.back()[1] = std::max(results.back()[1], intervals[i][1]);
                } else {
                    // No overlap, add current interval to results
                    results.push_back(intervals[i]);
                }
            }
            
            return results;
        }
    };