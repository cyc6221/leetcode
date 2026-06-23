class Solution {
public:
    long long bowlSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<pair<int,int>> a; a.reserve(n);
        for (int i = 0; i < n; ++i) a.push_back({nums[i], i});
        sort(a.rbegin(), a.rend());

        set<int> active;
        long long ans = 0;

        for (auto &[val, idx] : a) {
            auto it = active.lower_bound(idx);
            if (it != active.end()) {
                int r = *it;
                if (r - idx >= 2) ans++;
            }
            if (it != active.begin()) {
                int l = *prev(it);
                if (idx - l >= 2) ans++;
            }
            active.insert(idx);
        }
        return ans;
    }
};
