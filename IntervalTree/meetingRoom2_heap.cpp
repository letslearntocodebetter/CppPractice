/*

checking room availability: By comparing the start time of the current meeting with the smallest end time in the heap, we check if a room has been freed. 
If it has, we reuse that room (by removing the smallest end time from the heap).
Adding new meetings: Every meeting's end time is pushed onto the heap, 
which may increase the heap size, indicating the need for more rooms.
Heap Size: The size of the heap at the end of processing all meetings represents
 the maximum number of rooms used at any time, which is the answer.

*/



#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        // Sort the intervals by start time
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        // Min-heap to keep track of the end times of meetings
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Add the first meeting's end time to the heap
        minHeap.push(intervals[0][1]);

        for (int i = 1; i < intervals.size(); ++i) {
            // If the meeting can reuse the room
            if (intervals[i][0] >= minHeap.top()) {
                minHeap.pop();
            }
            // Push the end time of the current meeting onto the heap
            minHeap.push(intervals[i][1]);
        }

        // The size of the heap tells us the minimum number of rooms required
        return minHeap.size();
    }
};
