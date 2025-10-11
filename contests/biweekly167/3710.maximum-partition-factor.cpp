class Solution {
public:
    bool ok(vector<vector<long long>> &d, long long D) {
        int n = d.size();
        vector<vector<int>> adj(n);
        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                if(d[i][j] < D) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        vector<int> c(n, -1);
        for(int i=0; i<n; i++) {
            if(c[i] == -1) {
                queue<int> q;
                q.push(i);
                c[i] = 0;
                while(!q.empty()) {
                    int u = q.front(); q.pop();
                    for(int v : adj[u]) {
                        if(c[v] == -1) {
                            c[v] = c[u] ^ 1;
                            q.push(v);
                        }
                        else if(c[v] == c[u]) return false;
                    }
                }
            }
        }
        return true;
    }
    
    int maxPartitionFactor(vector<vector<int>>& p) {
        int n = p.size();
        if(n == 2) return 0;
        
        vector<vector<long long>> d(n, vector<long long>(n, 0));
        set<long long> L;
        
        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                d[i][j] = llabs((long long)p[i][0] - p[j][0]) +  llabs((long long)p[i][1] - p[j][1]);
                L.insert(d[i][j]);
            }
        }
        vector<long long> list(L.begin(), L.end());

        long long lo=0, hi=list.size()-1, mid;
        long long res = 0;
        vector<int> uf;
        while(lo <= hi) {
            mid = (lo + hi) / 2;

            if(ok(d, list[mid])) {
                res = list[mid];
                lo = mid + 1;
            }
            else {
                hi = mid - 1;
            }
        }
        return res;
    }
};