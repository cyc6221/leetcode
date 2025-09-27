# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> p, r;

    int find(int x) {
        if(p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    void unite(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return;
        if(r[a] < r[b]) swap(a, b);
        p[b] = a;
        if(r[a] == r[b]) r[a]++;
    }
    
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int n = nums.size();
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);

        for(auto& e : swaps) unite(e[0], e[1]);

        unordered_map<int, vector<int>> comp;
        comp.reserve(n*2);
        for(int i=0; i<n; i++) comp[find(i)].push_back(i);

        long long res = 0;
        vector<long long> vals;
        vals.reserve(n);

        for(auto& kv : comp) {
            const auto &idxs = kv.second;
            vals.clear();
            int k_even = 0;
            for(int i : idxs) {
                vals.push_back(nums[i]);
                if((i&1) == 0) k_even++;
            }
            sort(vals.begin(), vals.end(), greater<long long>());

            long long sumTopK = 0, sumRest = 0;
            for(int i=0; i<vals.size(); i++) {
                (i < k_even ? sumTopK : sumRest) += vals[i];
            }

            res += (sumTopK - sumRest);
        }

        return res;
    }
};