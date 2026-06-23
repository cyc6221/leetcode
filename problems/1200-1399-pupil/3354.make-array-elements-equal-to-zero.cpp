class Solution {
public:
    int countValidSelections(vector<int>& nums) {
        int sum = 0, temp = 0, res = 0;

        for(auto & i : nums) sum += i;
        
        for(auto & i : nums) {
            if(i == 0 && temp == sum - temp) res += 2;
            else if(i == 0 && abs(sum - temp - temp) == 1) res ++;
            temp += i;
        }

        return res;
    }
};