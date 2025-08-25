class Solution {
public:
    int minSensors(int n, int m, int k) {
        k = k * 2 + 1;
        int N = (n % k == 0) ? n / k : n / k + 1;
        int M = (m % k == 0) ? m / k : m / k + 1;

        return N * M;
    }
};