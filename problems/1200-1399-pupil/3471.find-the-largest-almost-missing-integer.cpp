class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        unordered_map<int, int> count;

        for(int i=0; i<nums.size(); i++) {
            if(i + k - 1 >= nums.size()) break;
            set<int> temp;
            for(int j=i; j<i+k; j++) {

                temp.insert(nums[j]);
            }
            for(auto& num : temp) {
                count[num]++;
            }
        }

        int res = -1;
        for(auto& [num, cnt] : count) {
            if(cnt == 1) {
                res = max(res, num);
            }
        }

        return res;
    }
};
