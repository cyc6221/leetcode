class Solution {
public:
    using ll = long long;
    int minRemoval(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();

        int res = 1;
        int l = 0, r = 0;

        for(l=0; l<n; l++) {
            while(r < n && (ll)nums[r] <= (ll)nums[l] * k) r++;
            res = max(res, r - l);
        }
        return n - res;
    }
};