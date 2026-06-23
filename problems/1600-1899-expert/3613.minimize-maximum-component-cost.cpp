class Solution {
public:
    int find(vector<int>& uf, int x) {
        if(uf[x] != x) {
            uf[x] = find(uf, uf[x]);
        }
        return uf[x];
    }
    int minCost(int n, vector<vector<int>>& edges, int k) {
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        int res = 0;

        vector<int> uf(n);
        for(int i=0; i<n; i++) {
            uf[i] = i;
        }

        set<int> root;
        for(int i=0; i<n; i++) {
            root.insert(i);
        }
        int index = 0;
        while(root.size() > k) {
            int u = edges[index][0];
            int v = edges[index][1];
            int w = edges[index][2];

            int ru = find(uf, u);
            int rv = find(uf, v);
            if(ru != rv) {
                if(ru < rv) {
                    uf[rv] = ru;
                    if(root.count(rv)) root.erase(rv);
                }
                else {
                    uf[ru] = rv;
                    if(root.count(ru)) root.erase(ru);
                }
                res = w;
            }
            index++;
        }

        return res;
    }
};
