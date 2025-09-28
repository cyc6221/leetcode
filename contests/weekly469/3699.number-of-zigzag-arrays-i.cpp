class Solution {
public:
    long long mod = 1e9+7;
    int zigZagArrays(int n, int l, int r) {
        long long m = r - l + 1;

        vector<long long> up(m), down(m);
        for(long long k = 0; k < m; k++) {
            up[k] = k % mod;
            down[k] = (m-1-k) % mod;
        }

        for(long long len = 3; len <= n; len++) {
            vector<long long> up2(m), down2(m);

            long long pre = 0;
            for(long long k = 0; k < m; k++) {
                up2[k] = pre;
                pre += down[k];
                if(pre >= mod) pre -= mod;
            }

            long long suf = 0;
            for(long long k = m-1; k>=0; k--) {
                down2[k] = suf;
                suf += up[k];
                if(suf >= mod) suf -= mod;
                if(k == 0) break;
            }

            up.swap(up2);
            down.swap(down2);
        }

        long long res = 0;
        for(long long k = 0; k < m; k++) {
            res += up[k];
            if(res >= mod) res -= mod;
        }
        for(long long k = 0; k < m; k++) {
            res += down[k];
            if(res >= mod) res -= mod;
        }

        return res % mod;
    }
};
