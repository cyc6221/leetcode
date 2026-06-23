class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        unordered_map<int, int> mp;
        for(auto& i : nums) mp[i]++;

        vector<int> vt;
        for(auto& i : mp) vt.push_back(i.first);
        sort(vt.begin(), vt.end());

        if(numOperations == 0 || k == 0) {
            int res = 0;
            for(auto& i : mp) res = max(res, i.second);
            return res;
        }
        
        int cur = 0;
        for(int i=vt[0]-1; i<=vt[0]-1+k; i++) {
            cur += mp[i];
        }
        int res = min(cur, numOperations);
        for(int i=vt[0]-1, j; i<=vt.back()+1; ) {
            cur -= mp[i-k];
            i++, j=i+k;
            cur -= mp[i];
            cur += mp[i+k];

            res = max(res, min(cur, numOperations) + mp[i]);
            cur += mp[i];
        }
        return res;
    }
};