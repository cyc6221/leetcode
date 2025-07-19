/*
 * @lc app=leetcode id=3541 lang=cpp
 *
 * [3541] Find Most Frequent Vowel and Consonant
 *
 * https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given a string s consisting of lowercase English letters ('a' to
 * 'z'). 
 * 
 * Your task is to:
 * 
 * 
 * Find the vowel (one of 'a', 'e', 'i', 'o', or 'u') with the maximum
 * frequency.
 * Find the consonant (all other letters excluding vowels) with the maximum
 * frequency.
 * 
 * 
 * Return the sum of the two frequencies.
 * 
 * Note: If multiple vowels or consonants have the same maximum frequency, you
 * may choose any one of them. If there are no vowels or no consonants in the
 * string, consider their frequency as 0.
 * The frequency of a letter x is the number of times it occurs in the
 * string.
 * 
 * Example 1:
 * 
 * 
 * Input: s = "successes"
 * 
 * Output: 6
 * 
 * Explanation:
 * 
 * 
 * The vowels are: 'u' (frequency 1), 'e' (frequency 2). The maximum frequency
 * is 2.
 * The consonants are: 's' (frequency 4), 'c' (frequency 2). The maximum
 * frequency is 4.
 * The output is 2 + 4 = 6.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "aeiaeia"
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * 
 * The vowels are: 'a' (frequency 3), 'e' ( frequency 2), 'i' (frequency 2).
 * The maximum frequency is 3.
 * There are no consonants in s. Hence, maximum consonant frequency = 0.
 * The output is 3 + 0 = 3.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 100
 * s consists of lowercase English letters only.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int maxFreqSum(string s) {
        unordered_map<char, int> ump;
        for(auto& i : s) ump[i] ++;

        int res1 = 0, res2 = 0;
        for(auto& i : ump) {
            if(i.first == 'a') res1 = max(res1, i.second);
            else if(i.first == 'e') res1 = max(res1, i.second);
            else if(i.first == 'i') res1 = max(res1, i.second);
            else if(i.first == 'o') res1 = max(res1, i.second);
            else if(i.first == 'u') res1 = max(res1, i.second);
            else res2 = max(res2, i.second);
        }
        return res1 + res2;
    }
};
// @lc code=end

