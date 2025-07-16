// Base to Integer Conversion: Convert string in base-n (2 ≤ base ≤ 36) to int
// Supports negative numbers and mixed-case input (e.g., "1A", "-2f")

#include <string>
#include <cctype>
#include <stdexcept>

using namespace std;

int charToDigit(char c) {
    if (isdigit(c)) return c - '0';
    if (isalpha(c)) return toupper(c) - 'A' + 10;
    throw invalid_argument("Invalid character in number");
}

int baseToInt(const string& s, int base) {
    if (base < 2 || base > 36)
        throw invalid_argument("Base must be between 2 and 36");

    int result = 0;
    int sign = 1;
    int i = 0;

    if (s[0] == '-') {
        sign = -1;
        i = 1;
    }

    for (; i < s.size(); ++i) {
        int digit = charToDigit(s[i]);
        if (digit >= base)
            throw invalid_argument("Digit out of range for base");

        result = result * base + digit;
    }

    return sign * result;
}

/* Example usage:
#include <iostream>
int main() {
    cout << baseToInt("11111111", 2) << "\n";     // 255
    cout << baseToInt("FF", 16) << "\n";          // 255
    cout << baseToInt("-2A", 16) << "\n";         // -42
    cout << baseToInt("73", 36) << "\n";          // 255
}
*/
