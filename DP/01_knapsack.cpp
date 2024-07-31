  //Function to return max value that can be put in knapsack of capacity W.
    int knapSack(int W, int wt[], int val[], int n) 
    { 
        // wirte the base codnition and valid input
        
        if (W==0 || n == 0) return 0;
        
        if (wt[n-1] <= W) {
                
            auto take = knapSack(W-wt[n-1], wt, val, n-1) + val[n-1];
            auto notTake = knapSack(W, wt, val, n-1);
            
            return std::max(take, notTake);
        }
        
        return knapSack(W, wt, val, n-1);
       
    }


using namespace std;
    // using dynamic programming
        int knapSack(int W, int wt[], int val[], int n) 
    { 
        // wirte the base codnition and valid input
        //base case
        // define a dp arry 
        vector<<vector<int>> dp (n+1, W+1);

        if (W==0 || n == 0) return 0;
        
        if (wt[n-1] <= W) {
                
            auto take = knapSack(W-wt[n-1], wt, val, n-1) + val[n-1];
            auto notTake = knapSack(W, wt, val, n-1);
            
            return std::max(take, notTake);
        }
        
        return knapSack(W, wt, val, n-1);
       
    }