#include <vector>
#include <algorithm>

class Solution {
public:
    int eraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        // Step 1: Sort by ending times
        std::sort(intervals.begin(), intervals.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
            return a[1] < b[1];  // Sort by end time
        });

        int count = 0;  // Number of intervals to remove
        int lastEnd = intervals[0][1];  // Store the last included interval's end

        // Step 2: Iterate through the intervals
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < lastEnd) {  
                // Overlapping case → Remove one interval
                count++;
            } else {  
                // No overlap → Update lastEnd
                lastEnd = intervals[i][1];
            }
        }

        return count;
    }
};
