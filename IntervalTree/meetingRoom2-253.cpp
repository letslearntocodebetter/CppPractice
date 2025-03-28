//
// sort begining and end positions
// check if the begining is more than end while iteration 
// we need a meeting room , else decrease the meeting room number


#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        // Separate start and end times and sort them
        vector<int> startTimes;
        vector<int> endTimes;
        
        for (const auto& interval : intervals) {
            startTimes.push_back(interval[0]);
            endTimes.push_back(interval[1]);
        }
        
        sort(startTimes.begin(), startTimes.end());
        sort(endTimes.begin(), endTimes.end());
        
        int startPointer = 0, endPointer = 0;
        int rooms = 0, maxRooms = 0;
        
        // this is the bound codition
        // if start is ended, we dont have to check the boudry condition for the endpohnint 
        // as start should come before end 
    
        
        // If a start time is less than the current end time, it means a new meeting is starting before the current one ends. So, we need a new room (rooms++).
        // If a start time is greater than or equal to the current end time, it means a meeting has ended, so we can reuse that room (rooms--).
        // We keep track of the maximum number of rooms needed at any point (maxRooms).
                
        
        while (startPointer < intervals.size()) {
            if (startTimes[startPointer] < endTimes[endPointer]) {
                // A new meeting has started
                rooms++;
                startPointer++;
            } else {
                // A meeting has ended
                rooms--;
                endPointer++;
            }
            maxRooms = max(maxRooms, rooms);
        }
        
        return maxRooms;
    }
};
