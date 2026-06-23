class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<bool> sum(k+1, 0), res(n, 0);
        sum[0] = 1;

        for(int i=0, x=1; x<=n; x++) {
            while(i < n && nums[i] < x) {
                for(int j=k; j>=nums[i]; j--) {
                    if(sum[j - nums[i]]) sum[j] = 1;
                }
                i++;
            }

            int cap = n-i;
            for(int j=0; j<=cap && j * x <= k; j++) {
                if(sum[k - j * x]) {
                    res[x-1] = 1;
                    break;
                }
            }
        }
        return res;
    }
};
