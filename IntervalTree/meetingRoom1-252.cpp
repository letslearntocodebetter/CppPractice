// check if the start of the next meeting is before end of the current meeting. If not the we cannot scheulde a meeting
// we have to sort the interval based on the starting point of the meeting and

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        // Sort intervals by start time
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        // Check for overlapping meetings
        for (int i = 1; i < intervals.size(); ++i) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                return false;
            }
        }

        return true;
    }
};
