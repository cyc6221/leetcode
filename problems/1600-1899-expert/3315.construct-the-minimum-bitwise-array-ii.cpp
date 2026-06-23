class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans(nums.size(), -1);
        for (int i = 0; i < nums.size(); i++) {
            if(nums[i] == 2) {
                ans[i] = -1;
            }
            else if(nums[i] % 2 == 1) {
                ans[i] = nums[i] - 1;
                if(nums[i] % 4 == 3) {
                    int q = 0, temp = nums[i];
                    while(temp & 1) {
                        temp >>= 1;
                        q++;
                    }
                    ans[i] = min(ans[i], nums[i] - (1 << q - 1));
                }
            }
        }
        return ans;
    }
};
