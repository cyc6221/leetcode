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
int count_components(const vector<int>& uf) {
    int count = 0;
    for (int i = 0; i < uf.size(); ++i) {
        if (uf[i] < 0) ++count;
    }
    return count;
}

    int minTime(int n, vector<vector<int>>& edges, int k) {
        vector<int> uf;
        init_union_find(uf, n);

        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] > b[2];
        });

        int merge = 0;
        for(int i=0; i<edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            if(!connected(uf, u, v)) {
                unite(uf, u, v);
                merge++;
                if(n - merge < k) {
                    return edges[i][2];
                }
            }

        }
        return 0;
    }
};
