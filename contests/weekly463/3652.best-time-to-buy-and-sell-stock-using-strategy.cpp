class Solution {
public:
long long maxProfit(vector<int>& p, vector<int>& s, int k) {
    int n = p.size();
    vector<long long> prefA(n + 1, 0), prefP(n + 1, 0);

    long long base = 0;
    for (int i = 0; i < n; ++i) {
        long long A = 1LL * p[i] * s[i];
        base += A;
        prefA[i + 1] = prefA[i] + A;
        prefP[i + 1] = prefP[i] + p[i];
    }

    int len = k / 2;
    long long res = base;

    for (int i = 0; i + k <= n; ++i) {
        long long sumA_window  = prefA[i + k] - prefA[i];
        long long sumP_second  = prefP[i + k] - prefP[i + len];
        long long cand = base - sumA_window + sumP_second;
        if (cand > res) res = cand;
    }
    return res;
}

};