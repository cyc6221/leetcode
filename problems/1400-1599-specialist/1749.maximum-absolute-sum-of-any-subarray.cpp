class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();

        vector<int> pre(n+1, 0);
        for(int i=1; i<=n; i++) {
            pre[i] = pre[i-1] + nums[i-1];
        }

        int ans = 0;
        int mx = pre[0], mn = pre[0];
        for(int i=1; i<=n; i++) {
            ans = max(ans, abs(pre[i] - mx));
            ans = max(ans, abs(pre[i] - mn));

            mn = min(mn, pre[i]);
            mx = max(mx, pre[i]);
        }

        return ans;
    }
};
