class Solution {
public:
    long long power(long long base, long long exp) {
        long long result = 1;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result *= base;
            }
            base *= base;
            exp /= 2;
        }
        return result;
    }

    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        long long num = power(2, maximumBit) - 1;
        vector<int> ans(nums.size());

        for(int i=0; i < nums.size(); i++) {
            num ^= nums[i];
            ans[nums.size() - 1 - i] = num;
        }

        return ans;
    }
};
