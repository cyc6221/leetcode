/*
 * @lc app=leetcode id=90 lang=cpp
 *
 * [90] Subsets II
 *
 * https://leetcode.com/problems/subsets-ii/description/
 *
 * algorithms
 * Medium (59.70%)
 * Likes:    10503
 * Dislikes: 381
 * Total Accepted:    1.3M
 * Total Submissions: 2.1M
 * Testcase Example:  '[1,2,2]'
 *
 * Given an integer array nums that may contain duplicates, return all possible
 * subsets (the power set).
 * 
 * The solution set must not contain duplicate subsets. Return the solution in
 * any order.
 * 
 * 
 * Example 1:
 * Input: nums = [1,2,2]
 * Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
 * Example 2:
 * Input: nums = [0]
 * Output: [[],[0]]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10
 * -10 <= nums[i] <= 10
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> ans;
    
    void back(vector<int>& cur, vector<int>& cnt, int index) {
        ans.push_back(cur);

        for(int i=index; i<21; i++) {
            if(cnt[i] == 0) continue;

            cur.push_back(i - 10);
            cnt[i]--;
            back(cur, cnt, i);

            cnt[i]++;
            cur.pop_back();
            // back(cur, cnt);
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> cnt(21, 0);
        for(int i=0; i<nums.size(); i++) {
            cnt[nums[i] + 10]++;
        }

        vector<int> cur;
        back(cur, cnt, 0);
        return ans;
    }
};
// @lc code=end

