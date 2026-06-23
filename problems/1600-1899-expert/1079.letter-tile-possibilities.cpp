/*
 * @lc app=leetcode id=1079 lang=cpp
 *
 * [1079] Letter Tile Possibilities
 *
 * https://leetcode.com/problems/letter-tile-possibilities/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * You have n  tiles, where each tile has one letter tiles[i] printed on it.
 * 
 * Return the number of possible non-empty sequences of letters you can make
 * using the letters printed on those tiles.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: tiles = "AAB"
 * Output: 8
 * Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB",
 * "ABA", "BAA".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: tiles = "AAABBC"
 * Output: 188
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: tiles = "V"
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= tiles.length <= 7
 * tiles consists of uppercase English letters.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int back(vector<int>& cnt) {
        int res = 0;
        for(int i=0; i < 26; i++) {
            if(cnt[i] > 0) {
                cnt[i]--;
                res += 1 + back(cnt);
                cnt[i]++;
            }
        }
        return res;
    }
    int numTilePossibilities(string tiles) {
        vector<int> cnt(26, 0);
        for(char c : tiles) {
            cnt[c - 'A']++;
        }

        return back(cnt);
    }
};
// @lc code=end

