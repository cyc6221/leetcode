class Solution {
public:
    vector<int> maxKDistinct(vector<int>& nums, int k) {
        sort(nums.rbegin(), nums.rend());
        vector<int> res;
        res.push_back(nums[0]);
        for(int i=1; i<nums.size(); i++) {
            if(res.size() == k) break;
            if(res.back() == nums[i]) continue;
            res.push_back(nums[i]);
        }
        return res;
    }
};