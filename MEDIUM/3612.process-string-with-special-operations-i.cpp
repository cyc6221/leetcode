/*
 * @lc app=leetcode id=3612 lang=cpp
 *
 * [3612] Process String with Special Operations I
 *
 * https://leetcode.com/problems/process-string-with-special-operations-i/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * You are given a string s consisting of lowercase English letters and the
 * special characters: *, #, and %.
 * 
 * Build a new string result by processing s according to the following rules
 * from left to right:
 * 
 * 
 * If the letter is a lowercase English letter append it to result.
 * A '*' removes the last character from result, if it exists.
 * A '#' duplicates the current result and appends it to itself.
 * A '%' reverses the current result.
 * 
 * 
 * Return the final string result after processing all characters in s.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "a#b%*"
 * 
 * Output: "ba"
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * i
 * s[i]
 * Operation
 * Current result
 * 
 * 
 * 
 * 
 * 0
 * 'a'
 * Append 'a'
 * "a"
 * 
 * 
 * 1
 * '#'
 * Duplicate result
 * "aa"
 * 
 * 
 * 2
 * 'b'
 * Append 'b'
 * "aab"
 * 
 * 
 * 3
 * '%'
 * Reverse result
 * "baa"
 * 
 * 
 * 4
 * '*'
 * Remove the last character
 * "ba"
 * 
 * 
 * 
 * 
 * Thus, the final result is "ba".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "z*#"
 * 
 * Output: ""
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * i
 * s[i]
 * Operation
 * Current result
 * 
 * 
 * 
 * 
 * 0
 * 'z'
 * Append 'z'
 * "z"
 * 
 * 
 * 1
 * '*'
 * Remove the last character
 * ""
 * 
 * 
 * 2
 * '#'
 * Duplicate the string
 * ""
 * 
 * 
 * 
 * 
 * Thus, the final result is "".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 20
 * s consists of only lowercase English letters and special characters *, #,
 * and %.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string processStr(string s) {
        string res;
        for(int i=0; i<s.size(); i++) {
            if(s[i] == '*') {
                if(res.length() > 0) res.pop_back();
            }
            else if(s[i] == '#') res += res;
            else if(s[i] == '%') reverse(res.begin(), res.end());
            else res += s[i];
        }
        return res;
    }
};
// @lc code=end

