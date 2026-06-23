class Solution {
public:
    int countHousePlacements(int n) {
        long long mod = 1e9+7, a=0, b=1, res = a+b;
        for(int i=1; i<=n; i++) {
            a = b;
            b = res;
            res = (a+b) % mod;
        }
        return (res * res) % mod;
    }
};