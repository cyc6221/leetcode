class Solution {
public:
    bool isTrionic(vector<int>& nums) {
        if(nums[0] > nums[1]) return false;
        int cnt = 0, pre = 1;
        for(int i=0; i+1<nums.size(); i++) {
            if(nums[i] < nums[i+1]) {
                if(pre == -1) pre = 1, cnt ++;
            }
            else if(nums[i] > nums[i+1]) {
                if(pre == 1) pre = -1, cnt++;
            }
            else return false;
        }
        return cnt == 2;
    }
};