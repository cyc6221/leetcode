/* Upsolving */

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

/* ===================================*/

/*

====== Fail to solve in contest ======

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
*/