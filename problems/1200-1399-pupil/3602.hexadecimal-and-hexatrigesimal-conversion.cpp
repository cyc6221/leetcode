class Solution {
public:
    string toBase36(int number) {
        const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            if (number == 0) return "0";

            string result;
            bool isNegative = number < 0;
            unsigned int n = isNegative ? -number : number;

            while (n > 0) {
                result += digits[n % 36];
                n /= 36;
            }

            if (isNegative)
                result += '-';

            reverse(result.begin(), result.end());
            return result;
    }

    string concatHex36(int n) {
        string hexadecimal = format("{:X}", n * n);
        string hexatrigesimal = toBase36(n * n * n);
        return hexadecimal + hexatrigesimal;
    }
};
