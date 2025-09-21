class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        long long mx = nums[0], mn = mx;
        for(auto& i : nums) {
            if(i > mx) mx = i;
            if(i < mn) mn = i;
        }

        long long res = mx - mn;
        res = res * (long long)k;
        return res;
    }
};