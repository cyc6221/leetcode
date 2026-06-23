class Solution {
public:

    void init_union_find(vector<int>& uf, int n) {
        uf.assign(n, -1);
    }

    int find(vector<int>& uf, int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf, uf[x]);
    }

    bool unite(vector<int>& uf, int x, int y) {
        x = find(uf, x);
        y = find(uf, y);
        if (x == y) return false;

        if (uf[x] > uf[y]) swap(x, y);
        uf[x] += uf[y];
        uf[y] = x;
        return true;
    }

    bool connected(vector<int>& uf, int x, int y) {
        return find(uf, x) == find(uf, y);
    }

    int size(vector<int>& uf, int x) {
        return -uf[find(uf, x)];
    }

    int maxStability(int n, vector<vector<int>>& edges, int k) {
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[3] != b[3]) return a[3] > b[3];
            return a[2] > b[2];
        });

        vector<int> uf(n);
        init_union_find(uf, n);

        int edge_count = 0;

        int must_edge = INT_MAX;
        vector<int> upgraded_edges;

        for(int i=0; i<edges.size(); i++) {
            if (edges[i][3] == 1) {
                if (!unite(uf, edges[i][0], edges[i][1])) {
                    return -1;
                }
                must_edge = min(must_edge, edges[i][2]);
                edge_count++;
            }
            else if (edges[i][3] == 0) {
                if(!unite(uf, edges[i][0], edges[i][1])) {
                    continue;
                }

                upgraded_edges.push_back(edges[i][2]);
                edge_count++;
            }
        }

        if(edge_count < n - 1) {
            return -1;
        }

        int upgraded_edge = INT_MAX;
        if(upgraded_edges.size() > 0) {
            sort(upgraded_edges.begin(), upgraded_edges.end());
            for(int i=0; k > 0 && i < upgraded_edges.size(); i++) {
                upgraded_edges[i] *= 2;
                k--;
            }
            upgraded_edge = *min_element(upgraded_edges.begin(), upgraded_edges.end());
        }

        int res = min(must_edge, upgraded_edge);
        return res;
    }
};
