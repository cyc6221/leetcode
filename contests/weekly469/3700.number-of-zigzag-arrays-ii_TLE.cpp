class Solution {
public:
    static constexpr long long mod = 1e9 + 7;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        if (m <= 0) return 0;

        std::vector<int> up(m), down(m);
        for (int k = 0; k < m; ++k) {
            up[k] = k;
        }

        long long suf = 0;
        for (int len = 2; len <= n; ++len) {
            suf = 0;
            for (int k = m - 1; k >= 0; --k) {
                down[m - 1 - k] = suf;
                suf += up[k];
                if (suf >= mod) suf -= mod;
            }
            if (len == n) break;
            up.swap(down);
        }

        return int((suf * 2) % mod);
    }
};
