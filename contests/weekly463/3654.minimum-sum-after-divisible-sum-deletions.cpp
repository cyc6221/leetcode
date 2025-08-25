class Solution {
public:
    long long minArraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + nums[i];

        long long total = prefix[n];
        long long removed = 0;

        vector<int> pos(k, -1);
        vector<int> seen(k, 0);
        int ver = 1;

        pos[0] = -1;
        seen[0] = ver;

        int cur_mod = 0;

        for (int i = 0; i < n; ++i) {
            cur_mod = (cur_mod + nums[i]) % k;

            if (seen[cur_mod] == ver) {
                int L = pos[cur_mod] + 1;
                int R = i;
                removed += prefix[R + 1] - prefix[L];

                ++ver;
                if (ver == INT_MAX) {
                    fill(seen.begin(), seen.end(), 0);
                    ver = 1;
                }
                pos[0] = i;
                seen[0] = ver;
                cur_mod = 0;
            } else {
                pos[cur_mod] = i;
                seen[cur_mod] = ver;
            }
        }

        return total - removed;
    }
};

// NOT FINISHED