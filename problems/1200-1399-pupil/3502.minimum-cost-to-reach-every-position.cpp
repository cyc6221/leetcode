class Solution {
public:
    vector<int> minCosts(vector<int>& cost) {
        vector<int> res(cost.size(), 0);
        int min = cost[0];
        for(int i=0; i<cost.size(); i++) {
            if(cost[i] < min) {
                min = cost[i];
            }
            res[i] = min;
        }
        return res;
    }
};
