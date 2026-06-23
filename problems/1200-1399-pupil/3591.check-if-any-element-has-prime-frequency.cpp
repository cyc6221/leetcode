/*
 * @lc app=leetcode id=3591 lang=cpp
 *
 * [3591] Check if Any Element Has Prime Frequency
 *
 * https://leetcode.com/problems/check-if-any-element-has-prime-frequency/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given an integer array nums.
 * 
 * Return true if the frequency of any element of the array is prime,
 * otherwise, return false.
 * 
 * The frequency of an element x is the number of times it occurs in the
 * array.
 * 
 * A prime number is a natural number greater than 1 with only two factors, 1
 * and itself.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,4,5,4]
 * 
 * Output: true
 * 
 * Explanation:
 * 
 * 4 has a frequency of two, which is a prime number.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,2,3,4,5]
 * 
 * Output: false
 * 
 * Explanation:
 * 
 * All elements have a frequency of one.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [2,2,2,4,4]
 * 
 * Output: true
 * 
 * Explanation:
 * 
 * Both 2 and 4 have a prime frequency.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 100
 * 0 <= nums[i] <= 100
 * 
 * 
 */

// @lc code=start
class Solution {

public:

    #define MAXN 1000005
    bitset<MAXN> is_prime;
    vector<int> primes;

    void sieve(int N) {
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;

        for (int i = 2; i <= N; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
                for (int j = i * 2; j <= N; j += i) {
                    is_prime[j] = 0;
                }
            }
        }
    }

    bool checkPrimeFrequency(vector<int>& nums) {
        int N = 100;
        sieve(N);

        unordered_map<int, int> freq;
        for (int num : nums) {
            freq[num]++;
        }

        for (auto it : freq) {
            int count = it.second;
            if (count <= N && is_prime[count]) {
                return true;
            }
        }

        return false; 
    }
};
// @lc code=end

