class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int res = 0;

        for (int i = 0; i < n; i++) {
            vector<int> cnt(26, 0);
            int distinct = 0;
            for (int j = i; j < n; j++) {
                int idx = s[j] - 'a';
                if (cnt[idx] == 0) distinct++;
                cnt[idx]++;

                int mn = INT_MAX, mx = 0;
                for (int c : cnt) {
                    if (c > 0) {
                        mn = min(mn, c);
                        mx = max(mx, c);
                    }
                }
                if (mn == mx)
                    res = max(res, j - i + 1);
            }
        }
        return res;
    }
};
