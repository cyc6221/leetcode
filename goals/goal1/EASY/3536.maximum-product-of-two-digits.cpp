/*
 * @lc app=leetcode id=3536 lang=cpp
 *
 * [3536] Maximum Product of Two Digits
 *
 * https://leetcode.com/problems/maximum-product-of-two-digits/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given a positive integer n.
 * 
 * Return the maximum product of any two digits in n.
 * 
 * Note: You may use the same digit twice if it appears more than once in n.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 31
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * 
 * The digits of n are [3, 1].
 * The possible products of any two digits are: 3 * 1 = 3.
 * The maximum product is 3.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 22
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * 
 * The digits of n are [2, 2].
 * The possible products of any two digits are: 2 * 2 = 4.
 * The maximum product is 4.
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 124
 * 
 * Output: 8
 * 
 * Explanation:
 * 
 * 
 * The digits of n are [1, 2, 4].
 * The possible products of any two digits are: 1 * 2 = 2, 1 * 4 = 4, 2 * 4 =
 * 8.
 * The maximum product is 8.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 10 <= n <= 10^9
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int maxProduct(int n) {
        vector<int> digits;
        while(n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
        sort(digits.rbegin(), digits.rend());
        return (digits[0]) * (digits[1]);
    }
};
// @lc code=end

