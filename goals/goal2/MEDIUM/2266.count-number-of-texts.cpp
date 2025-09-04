class Solution {
public:
    int countTexts(string k) {
        int n = k.length();
        long long res = 1, mod = 1e9+7;

        vector<long long> g1(n+1, 0), g2(n+1, 0);
        g1[0] = g2[0] = 1;
        for(int i=1; i<=n; i++) {
            if(i >= 1) g1[i] += g1[i-1], g2[i] += g2[i-1];
            if(i >= 2) g1[i] += g1[i-2], g2[i] += g2[i-2];
            if(i >= 3) g1[i] += g1[i-3], g2[i] += g2[i-3];
            if(i >= 4) g2[i] += g2[i-4];

            g1[i] %= mod, g2[i] %= mod;
        }
        
        for(int i=0; i<n; ) {
            char c = k[i];
            int cur = 0;
            while(i < n && k[i] == c) {
                cur++;
                i++;
            }

            // if(c == '7' || c == '9') res = res * g2[cur];
            // else res = res * g1[cur];
            res = (c == '7' || c == '9') ? res * g2[cur] : res * g1[cur];
            res %= mod;
        }

        return res;
    }
};