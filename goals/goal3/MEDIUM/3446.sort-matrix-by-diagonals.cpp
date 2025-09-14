class Solution {
public:
    vector<vector<int>> sortMatrix(vector<vector<int>>& g) {
        int n = g.size();

        vector<vector<int>> vt(n);
        for(int i=0; i<n; i++) {
            for(int j=0; j<=i; j++) {
                vt[i-j].push_back(g[i][j]);
            }
        }
        for(int i=0; i<n; i++) sort(vt[i].rbegin(), vt[i].rend());
        for(int i=0; i<n; i++) {
            for(int j=0; j<=i; j++) {
                g[i][j] = vt[i-j][j];
            }
        }

        vector<vector<int>> vt2(n+1);
        for(int j=1; j<n; j++) {
            for(int i=0; i<j; i++) {
                vt2[j-i].push_back(g[i][j]);
            }
        }
        for(int j=1; j<=n; j++) sort(vt2[j].begin(), vt2[j].end());
        for(int j=1; j<n; j++) {
            for(int i=0; i<j; i++) {
                g[i][j] = vt2[j-i][i];
            }
        }

        return g;
    }
};