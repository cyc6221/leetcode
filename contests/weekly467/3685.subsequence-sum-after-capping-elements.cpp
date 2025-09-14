class Solution {
public:
    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        int n = nums.size();
        vector<bool> ans(n, false);

        sort(nums.begin(), nums.end());
        // int mx = *max_element(nums.begin(), nums.end());
        // for(int i=n-1; i>=0; i--) if(nums[i] > k) nums[i] = k;
        int mx = nums.back();
        
        for (int cap = 1; cap <= n; cap++) {
            // if(cap > nums[n-1]) {
            if(cap > mx) {
                ans[cap-1] = ans[cap-2];
                continue;
            }
            if(cap * n < k) {
                // ans[cap-1] = false;
                continue;
            }
            
            bitset<4001> dp;
            dp[0] = 1;

            for (int& x : nums) {
                int val = min(x, cap);
                if (val > k) break;
                else if(val == k) {
                    dp[k] = 1;
                    break;
                }
                else {
                    dp |= (dp << val);
                    if(dp[k]) break;
                }
            }
            
            ans[cap-1] = dp[k];
        }
        
        return ans;
    }
};