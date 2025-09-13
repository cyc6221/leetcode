class Solution {
public:
    int maxXorSubsequences(vector<int>& nums) {
        vector<int> bs(32);
        for(int x : nums) {
            int v = x;
            for(int b=31; b>=0; b--) {
                if(((v >> b) & 1) == 0) continue;
                if(bs[b] == 0) {
                    bs[b] = v;
                    break;
                }
                v ^= bs[b];
            }
        }

        int res = 0;
        for(int b = 31; b>=0; b--) {
            if((res ^ bs[b]) > res) res ^= bs[b];
        }
        return res;
    }
};