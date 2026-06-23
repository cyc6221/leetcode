class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        vector<int> res(nums.size());
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] == 0) {
                res[i] = nums[i];
            }
            else if(nums[i] > 0) {
                int index = (i + nums[i]) % nums.size();
                res[i] = nums[index];
            }
            else if(nums[i] < 0) {
                int index = (i + nums[i] + 100 * nums.size()) % nums.size();
                res[i] = nums[index];
            }
        }
        return res;
    }
};
