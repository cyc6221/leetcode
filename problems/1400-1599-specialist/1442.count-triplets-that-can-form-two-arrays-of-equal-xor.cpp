/*
 * @lc app=leetcode id=1442 lang=cpp
 *
 * [1442] Count Triplets That Can Form Two Arrays of Equal XOR
 *
 * https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * Given an array of integers arr.
 * 
 * We want to select three indices i, j and k where (0 <= i < j <= k <
 * arr.length).
 * 
 * Let's define a and b as follows:
 * 
 * 
 * a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
 * b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
 * 
 * 
 * Note that ^ denotes the bitwise-xor operation.
 * 
 * Return the number of triplets (i, j and k) Where a == b.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [2,3,1,6,7]
 * Output: 4
 * Explanation: The triplets are (0,1,2), (0,2,2), (2,3,4) and (2,4,4)
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,1,1,1,1]
 * Output: 10
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= arr.length <= 300
 * 1 <= arr[i] <= 10^8
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int res = 0;
        for(int i=0; i < arr.size(); i++) {
            for(int j=i+1; j < arr.size(); j++) {
                for(int k=j; k < arr.size(); k++) {
                    int a = arr[i], b = arr[j];
                    for(int l=i+1; l < j; l++) {
                        a ^= arr[l];
                    }
                    for(int l=j+1; l <= k; l++) {
                        b ^= arr[l];
                    }
                    if(a == b) res++;
                }
            }
        }
        return res;
    }
};
// @lc code=end

