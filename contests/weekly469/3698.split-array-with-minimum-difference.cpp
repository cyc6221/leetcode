class Solution {
public:
    long long splitArray(vector<int>& nums) {
        int n = nums.size();

        vector<long long> pre(n + 1, 0);
        for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + nums[i];
        long long total = pre[n];

        vector<char> inc(n, 0), dec(n, 0);
        inc[0] = 1;
        for (int i = 1; i < n; ++i)
            inc[i] = inc[i - 1] && (nums[i - 1] < nums[i]);

        dec[n - 1] = 1;
        for (int i = n - 2; i >= 0; --i)
            dec[i] = dec[i + 1] && (nums[i] > nums[i + 1]);

        long long ans = LLONG_MAX;
        for (int k = 0; k <= n - 2; ++k) {
            if (inc[k] && dec[k + 1]) {
                long long left = pre[k + 1];
                long long right = total - left;
                ans = min(ans, llabs(right - left));
            }
        }
        
        return (ans == LLONG_MAX) ? -1 : ans;
    }
};
