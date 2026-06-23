class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int a = cost[0], b = cost[1];

        for(int i=2, t; i<cost.size(); i++) {
            t = min(a, b) + cost[i];
            a = b;
            b = t;
        }

        return min(a, b);

        // int n = cost.size();
        // vector<int> arr(n+1, INT_MAX);

        // arr[0] = arr[1] = 0;

        // for(int i=2; i<=n; i++) {
        //     arr[i] = min(arr[i-1]+cost[i-1], arr[i-2]+cost[i-2]);
        // }

        // return arr[n];
    }
};