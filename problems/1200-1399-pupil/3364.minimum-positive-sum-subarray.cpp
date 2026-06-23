class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int res = INT_MAX;
        for(int i=0; i<nums.size(); i++) {
            int cur = 0;
            for(int j=i; j<nums.size(); j++) {
                cur += nums[j];
                if(j-i+1 > r) break;
                if(j-i+1 >= l && cur > 0) {
                    res = min(res, cur);
                }
            }
        }
        return res == INT_MAX ? -1 : res;
    }
};
