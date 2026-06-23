/*
 * @lc app=leetcode id=3280 lang=cpp
 *
 * [3280] Convert Date to Binary
 *
 * https://leetcode.com/problems/convert-date-to-binary/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 *
 * You are given a string date representing a Gregorian calendar date in the
 * yyyy-mm-dd format.
 * 
 * date can be written in its binary representation obtained by converting
 * year, month, and day to their binary representations without any leading
 * zeroes and writing them down in year-month-day format.
 * 
 * Return the binary representation of date.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: date = "2080-02-29"
 * 
 * Output: "100000100000-10-11101"
 * 
 * Explanation:
 * 
 * 100000100000, 10, and 11101 are the binary representations of 2080, 02, and
 * 29 respectively.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: date = "1900-01-01"
 * 
 * Output: "11101101100-1-1"
 * 
 * Explanation:
 * 
 * 11101101100, 1, and 1 are the binary representations of 1900, 1, and 1
 * respectively.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * date.length == 10
 * date[4] == date[7] == '-', and all other date[i]'s are digits.
 * The input is generated such that date represents a valid Gregorian calendar
 * date between Jan 1^st, 1900 and Dec 31^st, 2100 (both inclusive).
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string convertDateToBinary(string date) {
        int year = 0, month = 0, day = 0;
        year += (date[0] - '0') * 1000;
        year += (date[1] - '0') * 100;
        year += (date[2] - '0') * 10;
        year += (date[3] - '0');

        month += (date[5] - '0') * 10;
        month += (date[6] - '0');

        day += (date[8] - '0') * 10;
        day += (date[9] - '0');

        string res1, res2, res3;
        while(year > 0) {
            res1 += to_string(year % 2);
            year /= 2;
        }
        reverse(res1.begin(), res1.end());
        while(month > 0) {
            res2 += to_string(month % 2);
            month /= 2;
        }
        reverse(res2.begin(), res2.end());
        while(day > 0) {
            res3 += to_string(day % 2);
            day /= 2;
        }
        reverse(res3.begin(), res3.end());

        string res = res1 + "-" + res2 + "-" + res3;
        return res;
    }
};
// @lc code=end

