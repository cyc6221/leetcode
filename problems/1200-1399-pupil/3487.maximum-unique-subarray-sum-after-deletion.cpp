class Solution {
public:
    int maxSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = nums[0];
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] < 0) {
                res = max(res, nums[i]);
                continue;
            }

            int sum = 0;
            set<int> s;
            while(i < nums.size()) {
                if(!s.count(nums[i])) {
                    s.insert(nums[i]);
                    sum += nums[i];
                }
                i++;
            }
            res = max(res, sum);
            break;
        }
        return res;
    }
};
