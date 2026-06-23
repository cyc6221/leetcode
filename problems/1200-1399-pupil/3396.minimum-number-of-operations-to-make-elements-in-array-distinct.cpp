class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int res = nums.size() / 3;
        if(nums.size() % 3 != 0) res ++;
        set<int> dis;
        for(int i=nums.size()-1; i>=0; i--) {
            if(dis.count(nums[i])) {
                break;
            }
            else {
                dis.insert(nums[i]);
                if(i % 3 == 0) res--;
            }
        }
        return res;
    }
};
