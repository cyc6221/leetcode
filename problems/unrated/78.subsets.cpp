class Solution {
public:
    vector<vector<int>> ans;

    void back(vector<int>& nums, vector<int>& cur, int i) {
        if(i == nums.size()) {
            ans.push_back(cur);
            return;
        }

        back(nums, cur, i + 1);
        cur.push_back(nums[i]);
        back(nums, cur, i + 1);
        cur.pop_back();
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> cur;
        back(nums, cur, 0);
        return ans;
    }
};
