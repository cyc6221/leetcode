/*
 * @lc app=leetcode id=3370 lang=cpp
 *
 * [3370] Smallest Number With All Set Bits
 *
 * https://leetcode.com/problems/smallest-number-with-all-set-bits/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given a positive number n.
 * 
 * Return the smallest number x greater than or equal to n, such that the
 * binary representation of x contains only set bits
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 5
 * 
 * Output: 7
 * 
 * Explanation:
 * 
 * The binary representation of 7 is "111".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 10
 * 
 * Output: 15
 * 
 * Explanation:
 * 
 * The binary representation of 15 is "1111".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 3
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * The binary representation of 3 is "11".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 1000
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int smallestNumber(int n) {
        int res = 1;
        while(n > res - 1) res *= 2;
        return res - 1;
    }
};
// @lc code=end

