class Solution {
public:
    vector<vector<int>> res;
    bool dfs(vector<vector<int>>& all, vector<vector<int>>& gm, int cur) {
        if(cur == all.size()) {
            res = gm;
            return true;
        }

        for(int i=0; i<all.size(); i++) {
            if(all[i][2]) continue;

            if(cur>0 && (all[i][0] == gm[cur-1][0] || all[i][0] == gm[cur-1][1])) continue;
            if(cur>0 && (all[i][1] == gm[cur-1][0] || all[i][1] == gm[cur-1][1])) continue;

            all[i][2] = 1;
            gm[cur][0] = all[i][0];
            gm[cur][1] = all[i][1];
            if(dfs(all, gm, cur+1)) return true;

            all[i][2] = 0;
        }
        return false;
    }
    vector<vector<int>> generateSchedule(int n) {
        vector<vector<int>> all;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                if(i == j) continue;
                all.push_back({i, j, 0});
            }
        }
        // cout << all.size() << endl;

        vector<vector<int>> gm(all.size(), vector<int>(2, -1));
        gm[0] = {all[0][0], all[0][1]};
        all[0][2] = 1;
        res = {{}};
        if(dfs(all, gm, 1)) return gm;
        else return {};

        return res;
    }
};