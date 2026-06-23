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
        
        // vector<long long> arr(high+1, 0);

        // for(int i=min(zero, one); i<=high; i++) {
        //     if(i == zero) arr[i] += 1;
        //     if(i == one) arr[i] += 1;

        //     if(i-zero > 0) arr[i] = (arr[i] + arr[i-zero]);
        //     if(i-one > 0) arr[i] = (arr[i] + arr[i-one]);
        //     arr[i] %= mod;

        //     if(i >= low) res = (res + arr[i]);
        //     res %= mod;
        // }

        // return res;
    }
};