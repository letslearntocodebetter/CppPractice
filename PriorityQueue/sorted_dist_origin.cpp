class Solution {
    public:
        double distance(const vector<int>& point) {
            return std::sqrt(point.at(0) * point.at(0) + 
                     point.at(1) * point.at(1));
        }
        vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
           // get the distrance
           // put it not a vector
           // sort the vector in decreasing order
            std::vector<std::pair<double, std::vector<int>>> dis; 
            auto foo = [this](const std::vector<int>& l, const std::vector<int> &r) {
              return (distance(l) < distance(r));
            };
           // T, Container<T>, std::greater<PAIR> pq(foo) 
            std::priority_queue<std::vector<int>, std::deque<std::vector<int>>, decltype(foo)> pq(foo);
            for (auto &point : points) {
                if (pq.size() >= k) {
                    const auto &top = pq.top();
                    if (distance(top) > distance(point)) {
                        pq.pop();
                    } else {
                        continue;
                    }
                }
                pq.emplace(std::move(point));
            }
            vector<vector<int>> anw;
            anw.reserve(k);
            for (auto i=0; i<k ;i++) {
                anw.emplace_back(std::move(pq.top()));
                pq.pop();
            }
            return anw;
        }
    
    
    
    };