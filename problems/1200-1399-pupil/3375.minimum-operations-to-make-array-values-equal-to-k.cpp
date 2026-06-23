class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        if(nums[0] < k) return -1;
        int op = 0;
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] > k) {
                op++;
            }
            while(i+1 < nums.size() && nums[i] == nums[i+1]) i++;
        }
        return op;
    }
};
