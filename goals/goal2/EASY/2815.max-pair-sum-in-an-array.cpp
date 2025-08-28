/*
 * @lc app=leetcode id=2815 lang=cpp
 *
 * [2815] Max Pair Sum in an Array
 *
 * https://leetcode.com/problems/max-pair-sum-in-an-array/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given an integer array nums. You have to find the maximum sum of a
 * pair of numbers from nums such that the largest digit in both numbers is
 * equal.
 * 
 * For example, 2373 is made up of three distinct digits: 2, 3, and 7, where 7
 * is the largest among them.
 * 
 * Return the maximum sum or -1 if no such pair exists.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [112,131,411]
 * 
 * Output: -1
 * 
 * Explanation:
 * 
 * Each numbers largest digit in order is [2,3,4].
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2536,1613,3366,162]
 * 
 * Output: 5902
 * 
 * Explanation:
 * 
 * All the numbers have 6 as their largest digit, so the answer is 2536 + 3366
 * = 5902.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [51,71,17,24,42]
 * 
 * Output: 88
 * 
 * Explanation:
 * 
 * Each number's largest digit in order is [5,7,7,4,4].
 * 
 * So we have only two possible pairs, 71 + 17 = 88 and 24 + 42 = 66.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= nums.length <= 100
 * 1 <= nums[i] <= 10^4
 * 
 * 
 */

// @lc code=start
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
// @lc code=end

