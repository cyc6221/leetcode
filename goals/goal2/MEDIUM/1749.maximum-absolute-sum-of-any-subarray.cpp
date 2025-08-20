/*
 * @lc app=leetcode id=1749 lang=cpp
 *
 * [1749] Maximum Absolute Sum of Any Subarray
 *
 * https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * You are given an integer array nums. The absolute sum of a subarray [numsl,
 * numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 +
 * numsr).
 * 
 * Return the maximum absolute sum of any (possibly empty) subarray of nums.
 * 
 * Note that abs(x) is defined as follows:
 * 
 * 
 * If x is a negative integer, then abs(x) = -x.
 * If x is a non-negative integer, then abs(x) = x.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,-3,2,3,-4]
 * Output: 5
 * Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,-5,1,-4,3,-2]
 * Output: 8
 * Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8)
 * = 8.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        // int mx = nums[0];

        vector<int> pre(n+1, 0);
        for(int i=1; i<=n; i++) {
            pre[i] = pre[i-1] + nums[i-1];
        }

        // for(int i=1; i<=n; i++) {
        //     for(int j=0; j<n; j++) {
        //         mx = max(mx, abs(pre[i] - pre[j]));
        //     }
        // }

        int ans = 0;
        int mx = pre[0], mn = pre[0];
        for(int i=1; i<=n; i++) {
            ans = max(ans, abs(pre[i] - mx));
            ans = max(ans, abs(pre[i] - mn));

            mn = min(mn, pre[i]);
            mx = max(mx, pre[i]);
        }

        return ans;
    }
};
// @lc code=end

