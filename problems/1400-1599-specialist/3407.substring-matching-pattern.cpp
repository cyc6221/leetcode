/*
 * @lc app=leetcode id=3407 lang=cpp
 *
 * [3407] Substring Matching Pattern
 *
 * https://leetcode.com/problems/substring-matching-pattern/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given a string s and a pattern string p, where p contains exactly
 * one '*' character.
 * 
 * The '*' in p can be replaced with any sequence of zero or more characters.
 * 
 * Return true if p can be made a substring of s, and false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "leetcode", p = "ee*e"
 * 
 * Output: true
 * 
 * Explanation:
 * 
 * By replacing the '*' with "tcod", the substring "eetcode" matches the
 * pattern.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "car", p = "c*v"
 * 
 * Output: false
 * 
 * Explanation:
 * 
 * There is no substring matching the pattern.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "luck", p = "u*"
 * 
 * Output: true
 * 
 * Explanation:
 * 
 * The substrings "u", "uc", and "uck" match the pattern.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 50
 * 1 <= p.length <= 50 
 * s contains only lowercase English letters.
 * p contains only lowercase English letters and exactly one '*'
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    bool hasMatch(string s, string p) {
        int star_pos = p.find('*');
        string prefix = p.substr(0, star_pos);
        string suffix = p.substr(star_pos + 1);
        // cout << "Prefix: " << prefix << ", Suffix: " << suffix << endl;

        if (prefix.length() + suffix.length() > s.length()) {
            return false;
        }
        
        for (int i = 0; i <= s.length() - prefix.length() - suffix.length(); i++) {
            if (s.substr(i, prefix.length()) != prefix) continue;
            
            for (int j = i + prefix.length(); j <= s.length() - suffix.length(); j++) {
                if (s.substr(j, suffix.length()) == suffix) {
                    return true;
                }
            }
        }
        
        return false;
    }
};
// @lc code=end

