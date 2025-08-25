class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& q) {
        long long res = 0;
        // for(auto& i : nums) res ^= i;
        for(int i=0; i<q.size(); i++) {
            long long l = q[i][0];
            long long r = q[i][1];
            long long k = q[i][2];
            long long v = q[i][3];
            // if((r - l) % k == 0) {
            //     res ^= v;
            // }
            // long long V = 1;
            while(l <= r) {
                // V = (V * v) % 1000000007;
                long long temp = nums[l];
                temp *= v;
                temp %= 1000000007;
                nums[l] = temp;
                l += k;
            }
            // res ^= V;
        }
        // for(auto& i : nums) cout << i << ' ';
        // cout << endl;
        for(auto& i : nums) res ^= i;
        return res;
    }
};