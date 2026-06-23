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
