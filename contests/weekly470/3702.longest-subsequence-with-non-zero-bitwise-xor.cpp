class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int res = 0, n = nums.size();
        bool z = true;
        for(auto & x : nums) {
            res ^= x;
            if(x != 0) z = false;
        }
        if(z) {
            return 0;
        }
        else if(res != 0) {
            return n;
        }
        else {
            return n-1;
        }
    }
};
