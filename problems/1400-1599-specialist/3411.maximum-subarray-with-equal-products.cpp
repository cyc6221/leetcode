class Solution {
public:
    int maxLength(vector<int>& nums) {
        int res = 0;
        for(int i=0; i<nums.size(); i++) {
            int prod_val = nums[i];
            int gcd_val = nums[i];
            int lcm_val = nums[i];

            for(int j=i+1; j<nums.size(); j++) {
                prod_val *= nums[j];
                gcd_val = gcd(gcd_val, nums[j]);
                lcm_val = lcm(lcm_val, nums[j]);

                if(prod_val == lcm_val * gcd_val) {
                    res = max(res, j-i+1);
                }
                else {
                    break;
                }
            }
        }
        return res;
    }
};
