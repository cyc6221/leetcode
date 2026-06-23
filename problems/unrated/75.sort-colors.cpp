class Solution {
public:
    void sortColors(vector<int>& nums) {
        int a = 0, b = 0, c = 0;
        for(auto& x : nums) {
            if(x == 0) a++;
            else if(x == 1) b++;
            else c++;
        }
        int i=0;
        for(int j=0; j<a; j++, i++) nums[i] = 0;
        for(int j=0; j<b; j++, i++) nums[i] = 1;
        for(int j=0; j<c; j++, i++) nums[i] = 2;
    }
};