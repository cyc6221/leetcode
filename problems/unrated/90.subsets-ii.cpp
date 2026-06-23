class Solution {
public:
    vector<vector<int>> ans;

    void back(vector<int>& cur, vector<int>& cnt, int index) {
        ans.push_back(cur);

        for(int i=index; i<21; i++) {
            if(cnt[i] == 0) continue;

            cur.push_back(i - 10);
            cnt[i]--;
            back(cur, cnt, i);

            cnt[i]++;
            cur.pop_back();

        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> cnt(21, 0);
        for(int i=0; i<nums.size(); i++) {
            cnt[nums[i] + 10]++;
        }

        vector<int> cur;
        back(cur, cnt, 0);
        return ans;
    }
};
