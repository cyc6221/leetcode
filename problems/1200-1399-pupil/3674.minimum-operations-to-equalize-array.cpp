class Solution {
public:
    int minOperations(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[0] == nums.back() ? 0 : 1;
    }
};