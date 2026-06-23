class Solution {
public:
    int smallestNumber(int n) {
        int res = 1;
        while(n > res - 1) res *= 2;
        return res - 1;
    }
};
