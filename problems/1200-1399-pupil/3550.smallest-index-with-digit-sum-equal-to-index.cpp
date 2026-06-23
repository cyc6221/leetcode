class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            int temp = 0;
            while(nums[i] > 0) {
                temp += nums[i] % 10;
                nums[i] /= 10;
            }
            if(temp == i) return i;
        }
        return -1;
    }
};
