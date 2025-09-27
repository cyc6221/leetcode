# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> res(n+1, INT_MAX);
        res[0] = 0;
        for(int i=0; i<n; i++) {
            if(i >= 0) {
                res[i+1] = min(res[i+1], res[i] + costs[i] + 1);
            }
            if(i-1 >= 0) {
                res[i+1] = min(res[i+1], res[i-1] + costs[i] + 4);
            }
            if(i-2 >= 0) {
                res[i+1] = min(res[i+1], res[i-2] + costs[i] + 9);
            }
        }
        return res[n];
    }
};