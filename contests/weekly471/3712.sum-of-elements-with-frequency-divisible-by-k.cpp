class Solution {
public:
    int sumDivisibleByK(vector<int>& nums, int k) {
        vector<int> cnt(110, 0);
        for(auto& i : nums) cnt[i]++;

        int res = 0;
        for(int i=1; i<=100; i++) {
            if(cnt[i] % k == 0) {
                res += i * cnt[i];
            }
        }
        return res;
    }
};