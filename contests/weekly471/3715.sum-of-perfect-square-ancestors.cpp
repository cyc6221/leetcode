class Solution {
public:
    long long res;
    int N;
    unordered_map<int, int> freq;

    int S(int x) {
        int res = 1;
        for(int p=2; p * p <= x; p++) {
            int cnt = 0;
            while(x % p == 0) {
                x /= p;
                cnt ^= 1;
            }
            if(cnt) res *= p;
        }
        if(x > 1) res *= x;
        return res;
    }

    void dfs(unordered_map<int, vector<int>> &adj, vector<int>& nums, vector<int>& vis, int cur) {
        if(vis[cur]) return;
        vis[cur] = 1;

        int key = S(nums[cur]);
        res += freq[key];
        freq[key]++;
        
        for(auto& b : adj[cur]) {
            if(b != cur) dfs(adj, nums, vis, b);
        }
        freq[key]--;
    }
    
    long long sumOfAncestors(int n, vector<vector<int>>& edges, vector<int>& nums) {
        res = 0;
        N = n;

        unordered_map<int, vector<int>> adj;

        for(auto& e : edges) {
            int a = e[0], b = e[1];
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<int> vis(n, 0);
        dfs(adj, nums, vis, 0);
        return res;
    }
};