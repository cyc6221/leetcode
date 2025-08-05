/*
 * @lc app=leetcode id=3487 lang=cpp
 *
 * [3487] Maximum Unique Subarray Sum After Deletion
 *
 * https://leetcode.com/problems/maximum-unique-subarray-sum-after-deletion/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given an integer array nums.
 * 
 * You are allowed to delete any number of elements from nums without making it
 * empty. After performing the deletions, select a subarray of nums such
 * that:
 * 
 * 
 * All elements in the subarray are unique.
 * The sum of the elements in the subarray is maximized.
 * 
 * 
 * Return the maximum sum of such a subarray.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,4,5]
 * 
 * Output: 15
 * 
 * Explanation:
 * 
 * Select the entire array without deleting any element to obtain the maximum
 * sum.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,1,0,1,1]
 * 
 * Output: 1
 * 
 * Explanation:
 * 
 * Delete the element nums[0] == 1, nums[1] == 1, nums[2] == 0, and nums[3] ==
 * 1. Select the entire array [1] to obtain the maximum sum.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,-1,-2,1,0,-1]
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * Delete the elements nums[2] == -1 and nums[3] == -2, and select the subarray
 * [2, 1] from [1, 2, 1, 0, -1] to obtain the maximum sum.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 100
 * -100 <= nums[i] <= 100
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int maxSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = nums[0];
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] < 0) {
                res = max(res, nums[i]);
                continue;
            }

            int sum = 0;
            set<int> s;
            while(i < nums.size()) {
                if(!s.count(nums[i])) {
                    s.insert(nums[i]);
                    sum += nums[i];
                }
                i++;
            }
            res = max(res, sum);
            break;
        }
        return res;
    }
};
// @lc code=end

