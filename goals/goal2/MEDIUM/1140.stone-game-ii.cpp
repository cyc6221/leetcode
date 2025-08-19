/*
 * @lc app=leetcode id=1140 lang=cpp
 *
 * [1140] Stone Game II
 *
 * https://leetcode.com/problems/stone-game-ii/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * Alice and Bob continue their games with piles of stones. There are a number
 * of piles arranged in a row, and each pile has a positive integer number of
 * stones piles[i]. The objective of the game is to end with the most stones.
 * 
 * Alice and Bob take turns, with Alice starting first.
 * 
 * On each player's turn, that player can take all the stones in the first X
 * remaining piles, where 1 <= X <= 2M. Then, we set M = max(M, X). Initially,
 * M = 1.
 * 
 * The game continues until all the stones have been taken.
 * 
 * Assuming Alice and Bob play optimally, return the maximum number of stones
 * Alice can get.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: piles = [2,7,9,4,4]
 * 
 * Output: 10
 * 
 * Explanation:
 * 
 * 
 * If Alice takes one pile at the beginning, Bob takes two piles, then Alice
 * takes 2 piles again. Alice can get 2 + 4 + 4 = 10 stones in total.
 * If Alice takes two piles at the beginning, then Bob can take all three piles
 * left. In this case, Alice get 2 + 7 = 9 stones in total.
 * 
 * 
 * So we return 10 since it's larger.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: piles = [1,2,3,4,5,100]
 * 
 * Output: 104
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= piles.length <= 100
 * 1 <= piles[i] <= 10^4
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int dfs(vector<vector<int>>& dp, vector<int>& suffix, int index, int M) {
        if(index >= suffix.size()) return 0;
        if(2 * M >= suffix.size() - index) return suffix[index];
        if(dp[index][M] != -1) return dp[index][M];

        int best = 0;
        for(int X = 1; X <= 2*M; X++) {
            best = max(best, suffix[index] - dfs(dp, suffix, index+X, max(M, X)));
        }
        return dp[index][M] = best;
    }
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        vector<int> suffix(n+1, 0);
        for(int i=n-1; i>=0; i--) {
            suffix[i] = suffix[i+1] + piles[i];
        }

        vector<vector<int>> dp(n, vector<int>(n+1, -1));

        return dfs(dp, suffix, 0, 1);
    }
};
// @lc code=end