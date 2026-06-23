class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        long long res = 0, mod = 1e9 + 7;
        vector<long long> dp(high+1, 0);
        dp[0] = 1;

        for(int i=1; i<=high; i++) {
            if(i >= zero) dp[i] += dp[i - zero];
            if(i >= one) dp[i] += dp[i - one];
            dp[i] %= mod;

            if(i >= low) {
                res += dp[i];
                res %= mod;
            }
        }
        return res;

    }
};
