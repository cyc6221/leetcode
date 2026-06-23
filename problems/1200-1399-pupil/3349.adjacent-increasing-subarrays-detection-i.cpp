class Solution {
public:
    bool hasIncreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i <= n - 2 * k; ++i) {
            bool ok = true;
            for (int j = i; j < i + k - 1; ++j) {
                if (nums[j] >= nums[j + 1]) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;
            for (int j = i + k; j < i + 2 * k - 1; ++j) {
                if (nums[j] >= nums[j + 1]) {
                    ok = false;
                    break;
                }
            }
            if (ok) return true;
        }
        return false;
    }
};
