/*
 * @lc app=leetcode id=1185 lang=cpp
 *
 * [1185] Day of the Week
 *
 * https://leetcode.com/problems/day-of-the-week/description/
 *
 * Category: algorithms
 * Difficulty: Easy
 * 
 * Given a date, return the corresponding day of the week for that date.
 * 
 * The input is given as three integers representing the day, month and year
 * respectively.
 * 
 * Return the answer as one of the following values {"Sunday", "Monday",
 * "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: day = 31, month = 8, year = 2019
 * Output: "Saturday"
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: day = 18, month = 7, year = 1999
 * Output: "Sunday"
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: day = 15, month = 8, year = 1993
 * Output: "Sunday"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The given dates are valid dates between the years 1971 and 2100.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string dayOfTheWeek(int day, int month, int year) {
        if (month <= 2) {
            month += 12;
            year -= 1;
        }
        int K = year % 100; 
        int J = year / 100;
        int h = (day + (13 * (month + 1)) / 5 + K + K/4 + J/4 + 5*J) % 7;
        int w = (h + 6) % 7;

        vector<string> names = {
            "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"
        };
        return names[w];
    }
};
// @lc code=end

