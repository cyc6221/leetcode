class Solution {
public:
    bool checkDivisibility(int n) {
        int a = 0, b = 1, num = n;
        while(num > 0) {
            a += num % 10;
            b *= num % 10;
            num /= 10;
        }
        return (n % (a + b) == 0) ? true : false;
    }
};