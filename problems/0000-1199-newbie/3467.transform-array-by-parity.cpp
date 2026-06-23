class Solution {
public:
    vector<int> transformArray(vector<int>& nums) {
        vector<int> res(nums.size(), 1);
        int t = 0;
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] % 2 == 0) {
                res[t] = 0;
                t++;
            }
        }
        return res;
    }
};
