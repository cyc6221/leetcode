/*
 * @lc app=leetcode id=78 lang=cpp
 *
 * [78] Subsets
 *
 * https://leetcode.com/problems/subsets/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * Given an integer array nums of unique elements, return all possible subsets
 * (the power set).
 * 
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3]
 * Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0]
 * Output: [[],[0]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * All the numbers of nums are unique.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> ans;
    
    void back(vector<int>& nums, vector<int>& cur, int i) {
        if(i == nums.size()) {
            ans.push_back(cur);
            return;
        }
        
        back(nums, cur, i + 1);
        cur.push_back(nums[i]);
        back(nums, cur, i + 1);
        cur.pop_back();
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> cur;
        back(nums, cur, 0);
        return ans;
    }
};
// @lc code=end

