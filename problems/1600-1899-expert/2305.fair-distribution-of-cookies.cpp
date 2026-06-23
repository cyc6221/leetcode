/*
 * @lc app=leetcode id=2305 lang=cpp
 *
 * [2305] Fair Distribution of Cookies
 *
 * https://leetcode.com/problems/fair-distribution-of-cookies/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * You are given an integer array cookies, where cookies[i] denotes the number
 * of cookies in the i^th bag. You are also given an integer k that denotes the
 * number of children to distribute all the bags of cookies to. All the cookies
 * in the same bag must go to the same child and cannot be split up.
 * 
 * The unfairness of a distribution is defined as the maximum total cookies
 * obtained by a single child in the distribution.
 * 
 * Return the minimum unfairness of all distributions.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: cookies = [8,15,10,20,8], k = 2
 * Output: 31
 * Explanation: One optimal distribution is [8,15,8] and [10,20]
 * - The 1^st child receives [8,15,8] which has a total of 8 + 15 + 8 = 31
 * cookies.
 * - The 2^nd child receives [10,20] which has a total of 10 + 20 = 30 cookies.
 * The unfairness of the distribution is max(31,30) = 31.
 * It can be shown that there is no distribution with an unfairness less than
 * 31.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: cookies = [6,1,3,2,2,4,1,2], k = 3
 * Output: 7
 * Explanation: One optimal distribution is [6,1], [3,2,2], and [4,1,2]
 * - The 1^st child receives [6,1] which has a total of 6 + 1 = 7 cookies.
 * - The 2^nd child receives [3,2,2] which has a total of 3 + 2 + 2 = 7
 * cookies.
 * - The 3^rd child receives [4,1,2] which has a total of 4 + 1 + 2 = 7
 * cookies.
 * The unfairness of the distribution is max(7,7,7) = 7.
 * It can be shown that there is no distribution with an unfairness less than
 * 7.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= cookies.length <= 8
 * 1 <= cookies[i] <= 10^5
 * 2 <= k <= cookies.length
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int min_unfairness = INT_MAX;

    void dis(vector<int>& cookies, int k, int i_cook, vector<int>& child) {
        if(i_cook == cookies.size()) {
            int max_cookies = 0;
            for(int i = 0; i < k; i++) {
                max_cookies = max(max_cookies, child[i]);
            }
            min_unfairness = min(min_unfairness, max_cookies);
            return;
        }

        for(int i = 0; i < k; i++) {
            child[i] += cookies[i_cook];
            dis(cookies, k, i_cook + 1, child);
            child[i] -= cookies[i_cook];
        }
    }

    int distributeCookies(vector<int>& cookies, int k) {
        vector<int> child(k, 0);
        min_unfairness = INT_MAX;
        dis(cookies, k, 0, child);
        return min_unfairness;
    }
};
// @lc code=end

