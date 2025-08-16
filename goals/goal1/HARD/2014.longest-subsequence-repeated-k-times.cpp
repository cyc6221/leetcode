/*
 * @lc app=leetcode id=2014 lang=cpp
 *
 * [2014] Longest Subsequence Repeated k Times
 *
 * https://leetcode.com/problems/longest-subsequence-repeated-k-times/description/
 *
 * Category: algorithms
 * Difficulty: Hard
 *
 * You are given a string s of length n, and an integer k. You are tasked to
 * find the longest subsequence repeated k times in string s.
 * 
 * A subsequence is a string that can be derived from another string by
 * deleting some or no characters without changing the order of the remaining
 * characters.
 * 
 * A subsequence seq is repeated k times in the string s if seq * k is a
 * subsequence of s, where seq * k represents a string constructed by
 * concatenating seq k times.
 * 
 * 
 * For example, "bba" is repeated 2 times in the string "bababcba", because the
 * string "bbabba", constructed by concatenating "bba" 2 times, is a
 * subsequence of the string "bababcba".
 * 
 * 
 * Return the longest subsequence repeated k times in string s. If multiple
 * such subsequences are found, return the lexicographically largest one. If
 * there is no such subsequence, return an empty string.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "letsleetcode", k = 2
 * Output: "let"
 * Explanation: There are two longest subsequences repeated 2 times: "let" and
 * "ete".
 * "let" is the lexicographically largest one.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "bb", k = 2
 * Output: "b"
 * Explanation: The longest subsequence repeated 2 times is "b".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "ab", k = 2
 * Output: ""
 * Explanation: There is no subsequence repeated 2 times. Empty string is
 * returned.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == s.length
 * 2 <= k <= 2000
 * 2 <= n < min(2001, k * 8)
 * s consists of lowercase English letters.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string res;

    bool repeat(string& s, string &pat, int k) {
        if(pat.empty()) return true;

        int cnt = 0, pos = 0;

        for(char c : s) {
            if(c == pat[pos]) {
                pos = (pos + 1) % pat.length();
                if(pos == 0) {
                    cnt++;
                    if(cnt == k) return true;
                }
            }
        }
        return false;
    }

    void back(string& s, int k, string cur) {
        if(cur.length() >= res.length()) {
            res = max(res, cur);
            // return;
        }

        for (char c = 'a'; c <= 'z'; c++) {
            cur.push_back(c);
            if(repeat(s, cur, k)) back(s, k, cur);
            cur.pop_back();
        }
    }

    string longestSubsequenceRepeatedK(string s, int k) {
        vector<int> cnt(26, 0);
        for(char c : s) {
            cnt[c - 'a']++;
        }
        string temp;
        for(char c : s) {
            if(cnt[c - 'a'] >= k) {
                temp += c;
            }
        }
        s = temp;
        res = "";
        back(s, k, res);
        return res;
    }
};
// @lc code=end