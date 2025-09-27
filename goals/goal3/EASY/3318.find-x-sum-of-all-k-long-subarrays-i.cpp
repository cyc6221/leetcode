# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<int> res;
        for(int i=0; i+k<=n; i++) {
            unordered_map<int, int> f;
            for(int j=i; j<i+k; j++) f[nums[j]]++;
            vector<pair<int, int>> v;
            for(auto& p : f) v.push_back({p.second, p.first});
            sort(v.begin(), v.end(), [](auto &a, auto &b){
                if(a.first != b.first) return a.first > b.first;
                return a.second > b.second;
            });
            int sum = 0;
            int cnt = 0;
            for(auto& p : v) {
                if(cnt++ == x) break;
                sum += 1LL * p.first * p.second;
            }
            res.push_back(sum);
        }
        return res;

    }
};