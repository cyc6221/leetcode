class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int op = 0, inc = 0, mn, add, i;

        while(!inc) {
            vector<int> temp;
            inc = 1;
            mn = INT_MAX;

            for(i=0; i+1<nums.size(); i++) {
                if(nums[i] > nums[i+1]) inc = 0;
                mn = min(mn, nums[i] + nums[i+1]);
            }
            if(inc == 1) break;

            add = 0;
            for(i=0; i+1<nums.size() && !add; i++) {
                if(nums[i] + nums[i+1] == mn) {
                    temp.push_back(mn);
                    i++;
                    add = 1;
                }
                else temp.push_back(nums[i]);
            }
            while(i < nums.size()) {
                temp.push_back(nums[i]);
                i++;
            }

            nums = temp;
            op++;
        }
        return op;
    }
};
