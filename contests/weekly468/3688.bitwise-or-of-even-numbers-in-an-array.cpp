class Solution {
public:
    int evenNumberBitwiseORs(vector<int>& nums) {
        int res = 0;
        for(auto& a : nums) {
            if(a % 2 == 0) res |= a;
        }
        return res;
    }
};