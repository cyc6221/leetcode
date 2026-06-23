/*
 * @lc app=leetcode id=3507 lang=cpp
 *
 * [3507] Minimum Pair Removal to Sort Array I
 *
 * https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * Given an array nums, you can perform the following operation any number of
 * times:
 * 
 * 
 * Select the adjacent pair with the minimum sum in nums. If multiple such
 * pairs exist, choose the leftmost one.
 * Replace the pair with their sum.
 * 
 * 
 * Return the minimum number of operations needed to make the array
 * non-decreasing.
 * 
 * An array is said to be non-decreasing if each element is greater than or
 * equal to its previous element (if it exists).
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [5,2,3,1]
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * 
 * The pair (3,1) has the minimum sum of 4. After replacement, nums =
 * [5,2,4].
 * The pair (2,4) has the minimum sum of 6. After replacement, nums = [5,6].
 * 
 * 
 * The array nums became non-decreasing in two operations.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,2]
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * The array nums is already sorted.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 50
 * -1000 <= nums[i] <= 1000
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int op = 0, inc = 0, mn, add, i;

        while(!inc) {
            vector<int> temp;
            inc = 1;
            mn = INT_MAX;

            for(i=0; i+1<nums.size(); i++) {
                if(nums[i] > nums[i+1]) inc = 0;
                mn = min(mn, nums[i] + nums[i+1]);
            }
            if(inc == 1) break;

            add = 0;
            for(i=0; i+1<nums.size() && !add; i++) {
                if(nums[i] + nums[i+1] == mn) {
                    temp.push_back(mn);
                    i++;
                    add = 1;
                }
                else temp.push_back(nums[i]);
            }
            while(i < nums.size()) {
                temp.push_back(nums[i]);
                i++;
            }
            // cout << nums.size() << ' ' << temp.size() << endl;
            nums = temp;
            op++;
        }
        return op;
    }
};
// @lc code=end

