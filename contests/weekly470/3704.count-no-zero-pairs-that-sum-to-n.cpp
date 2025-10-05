class Solution {
public:
    vector<int> digits;
    long long dp[20][2][2][2][2][2];
    bool vis[20][2][2][2][2][2];
    
    long long dfs(int pos, int carry, int usedA, int usedB, int endA, int endB) {
        if (pos == digits.size()) {
            return (carry == 0 && usedA && usedB) ? 1LL : 0LL;
        }
        if (vis[pos][carry][usedA][usedB][endA][endB])
            return dp[pos][carry][usedA][usedB][endA][endB];
    
        long long res = 0;
        int t = digits[pos];
    
        for (int da = 0; da <= 9; ++da) {
            if (endA && da != 0) continue;
            int nEndA = endA || (da == 0);
            for (int db = 0; db <= 9; ++db) {
                if (endB && db != 0) continue;
                int nEndB = endB || (db == 0);
    
                int s = da + db + carry;
                if (s % 10 != t) continue;
    
                res += dfs(pos + 1, s / 10,
                           usedA || (da != 0),
                           usedB || (db != 0),
                           nEndA, nEndB);
            }
        }
    
        vis[pos][carry][usedA][usedB][endA][endB] = true;
        return dp[pos][carry][usedA][usedB][endA][endB] = res;
    }

    long long countNoZeroPairs(long long n) {
        digits.clear();
        
        while(n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }
        
        memset(vis, 0, sizeof(vis));
        return dfs(0, 0, 0, 0, 0, 0);
    }
};
