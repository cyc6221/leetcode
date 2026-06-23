/*
 * @lc app=leetcode id=3402 lang=cpp
 *
 * [3402] Minimum Operations to Make Columns Strictly Increasing
 *
 * https://leetcode.com/problems/minimum-operations-to-make-columns-strictly-increasing/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given a m x n matrix grid consisting of non-negative integers.
 * 
 * In one operation, you can increment the value of any grid[i][j] by 1.
 * 
 * Return the minimum number of operations needed to make all columns of grid
 * strictly increasing.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[3,2],[1,3],[3,4],[0,1]]
 * 
 * Output: 15
 * 
 * Explanation:
 * 
 * 
 * To make the 0^th column strictly increasing, we can apply 3 operations on
 * grid[1][0], 2 operations on grid[2][0], and 6 operations on grid[3][0].
 * To make the 1^st column strictly increasing, we can apply 4 operations on
 * grid[3][1].
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[3,2,1],[2,1,0],[1,2,3]]
 * 
 * Output: 12
 * 
 * Explanation:
 * 
 * 
 * To make the 0^th column strictly increasing, we can apply 2 operations on
 * grid[1][0], and 4 operations on grid[2][0].
 * To make the 1^st column strictly increasing, we can apply 2 operations on
 * grid[1][1], and 2 operations on grid[2][1].
 * To make the 2^nd column strictly increasing, we can apply 2 operations on
 * grid[1][2].
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 50
 * 0 <= grid[i][j] < 2500
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int res = 0;
        for(int j=0; j < grid[0].size(); j++) {
            int prev = grid[0][j];
            for(int i=1; i < grid.size(); i++) {
                if(prev >= grid[i][j]) {
                    res += prev - grid[i][j] + 1;
                    prev++;
                }
                prev = max(prev, grid[i][j]);
            }
        }
        return res;    
    }
};
// @lc code=end

