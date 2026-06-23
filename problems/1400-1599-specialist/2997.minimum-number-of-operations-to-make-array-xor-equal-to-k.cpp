class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int n = k;
        for(int num : nums) {
            n ^= num;
        }
        int res = 0;
        while (n > 0) {
            if(n % 2 == 1) res++;
            n /= 2;
        }
        return res;
    }
};
