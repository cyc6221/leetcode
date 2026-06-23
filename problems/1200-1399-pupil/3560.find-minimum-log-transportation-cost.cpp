class Solution {
public:
    long long minCuttingCost(int n, int m, int k) {
        long long res = 0;
        if(n > k) {
            long long a = n - k;
            long long b = k;
            res += a * b;
        }
        if(m > k) {
            long long a = m - k;
            long long b = k;
            res += a * b;
        }
        return res;
    }
};
