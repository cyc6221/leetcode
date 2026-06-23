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
