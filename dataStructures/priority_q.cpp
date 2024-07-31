comparision funciton neededs to be defined in it is not a less ie max priority queue and


for min priority queue use std::greater<int> 

auto comp = [](const std::pair<int, int>& l, const std::pair<int, int>& r) {
        return l.second < r.second;
    };

std::priority_queue<
        std::pair<int, int>, 
        std::vector<std::pair<int, int>>, 
        std::function<bool(const std::pair<int, int>&, const std::pair<int, int>&)>
    > pq(comp); <== give the comparator function here.

or you can use decltype(comp)

    emplace to push and to pop to take out. Top for the peaking the element.
================================================================

