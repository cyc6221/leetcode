/*
 * @lc app=leetcode id=735 lang=cpp
 *
 * [735] Asteroid Collision
 *
 * https://leetcode.com/problems/asteroid-collision/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * We are given an array asteroids of integers representing asteroids in a row.
 * The indices of the asteriod in the array represent their relative position
 * in space.
 * 
 * For each asteroid, the absolute value represents its size, and the sign
 * represents its direction (positive meaning right, negative meaning left).
 * Each asteroid moves at the same speed.
 * 
 * Find out the state of the asteroids after all collisions. If two asteroids
 * meet, the smaller one will explode. If both are the same size, both will
 * explode. Two asteroids moving in the same direction will never meet.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: asteroids = [5,10,-5]
 * Output: [5,10]
 * Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never
 * collide.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: asteroids = [8,-8]
 * Output: []
 * Explanation: The 8 and -8 collide exploding each other.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: asteroids = [10,2,-5]
 * Output: [10]
 * Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide
 * resulting in 10.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= asteroids.length <= 10^4
 * -1000 <= asteroids[i] <= 1000
 * asteroids[i] != 0
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> res;
        for (int a : asteroids) {
            bool destroyed = false;
            // 檢查當前小行星 a 是否會與 res 中最後一顆右移小行星碰撞
            while (!res.empty() && a < 0 && res.back() > 0) {
                if (res.back() < -a) {
                    // res 最後一顆小行星比 a 小，被撞碎，繼續檢查前一顆
                    res.pop_back();
                    continue;
                } 
                else if (res.back() == -a) {
                    // 相等，兩顆都爆炸
                    res.pop_back();
                }
                // a 被撞碎
                destroyed = true;
                break;
            }
            if (!destroyed) res.push_back(a);
        }
        return res;
    }
};
// @lc code=end

