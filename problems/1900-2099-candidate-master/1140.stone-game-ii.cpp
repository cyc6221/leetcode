class Solution {
public:
    int dfs(vector<vector<int>>& dp, vector<int>& suffix, int index, int M) {
        if(index >= suffix.size()) return 0;
        if(2 * M >= suffix.size() - index) return suffix[index];
        if(dp[index][M] != -1) return dp[index][M];

        int best = 0;
        for(int X = 1; X <= 2*M; X++) {
            best = max(best, suffix[index] - dfs(dp, suffix, index+X, max(M, X)));
        }
        return dp[index][M] = best;
    }
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        vector<int> suffix(n+1, 0);
        for(int i=n-1; i>=0; i--) {
            suffix[i] = suffix[i+1] + piles[i];
        }

        vector<vector<int>> dp(n, vector<int>(n+1, -1));

        return dfs(dp, suffix, 0, 1);
    }
};
