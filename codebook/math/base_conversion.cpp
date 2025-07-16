// Base Conversion: Convert integer to base-n (2 ≤ base ≤ 36)
// Supports negative numbers; output uses uppercase letters for bases > 10

#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

string intToBase(int number, int base) {
    const char* digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (base < 2 || base > 36)
        throw invalid_argument("Base must be between 2 and 36");

    if (number == 0) return "0";

    string result;
    bool isNegative = number < 0;
    unsigned int n = isNegative ? -number : number;

    while (n > 0) {
        result += digits[n % base];
        n /= base;
    }

    if (isNegative)
        result += '-';

    reverse(result.begin(), result.end());
    return result;
}

/* Example usage:
#include <iostream>
int main() {
    cout << intToBase(255, 2) << "\n";   // binary: 11111111
    cout << intToBase(255, 8) << "\n";   // octal: 377
    cout << intToBase(255, 10) << "\n";  // decimal: 255
    cout << intToBase(255, 16) << "\n";  // hex: FF
    cout << intToBase(255, 36) << "\n";  // base-36: 73
    cout << intToBase(-42, 16) << "\n";  // negative hex: -2A
}
*/
