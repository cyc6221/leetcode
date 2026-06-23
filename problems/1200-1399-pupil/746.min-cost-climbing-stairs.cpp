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

    }
};
