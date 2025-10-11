class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        if(nums.size() == 1) return true;
        if(nums.size() == 2) return true;

        int res = 0, cur = 0;
        for(int i=0; i+2<nums.size(); i++) {
            if(nums[i+2] == nums[i] + nums[i+1]) cur ++;
            else cur = 0;
            res = max(res, cur+2);
        }
        return res;
    }
};