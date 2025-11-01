/ LeetCode 547: Number of Provinces
// Problem: Given an n x n matrix where matrix[i][j] = 1 means person i and j are friends,
// find the total number of friend circles (provinces).

class Solution {
private:
    class UnionFind {
    private:
        vector<int> parent;
        vector<int> rank;
        int components;
        
    public:
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            components = n;
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        
        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            
            if (rootX == rootY) return;
            
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            components--;  // Merged two components
        }
        
        int getComponents() {
            return components;
        }
    };
    
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        UnionFind uf(n);
        
        // Unite all connected people
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    uf.unite(i, j);
                }
            }
        }
        
        return uf.getComponents();
    }
};
