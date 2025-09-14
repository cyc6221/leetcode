class Solution {
public:
    int earliestTime(vector<vector<int>>& tasks) {
        int res = tasks[0][0] + tasks[0][1];
        for(int i=1; i<tasks.size(); i++) {
            res = min(res,tasks[i][0] + tasks[i][1]);
        }
        return res;
    }
};