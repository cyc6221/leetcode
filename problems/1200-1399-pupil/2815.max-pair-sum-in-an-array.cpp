class Solution {
public:
    int maxSum(vector<int>& nums) {
        sort(nums.rbegin(), nums.rend());
        vector<vector<int>> vt(10);

        for(int i=0; i<nums.size(); i++) {
            int x = -1;
            for(int temp = nums[i]; temp>0; temp/=10) {
                x = max(x, temp%10);
            }
            vt[x].push_back(nums[i]);
        }

        int res = -1;
        for(int i=0; i<10; i++) {
            if(vt[i].size() > 1) {
                res = max(res, vt[i][0] + vt[i][1]);
            }
        }
        return res;
    }
};
