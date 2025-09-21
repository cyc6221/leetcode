class Solution {
public:
    int minSplitMerge(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        if (nums1 == nums2) return 0;
    
        queue<vector<int>> q;
        map<vector<int>, int> dist;
        q.push(nums1);
        dist[nums1] = 0;
    
        while (!q.empty()) {
            auto cur = q.front(); q.pop();
            int d = dist[cur];
    
            for (int L = 0; L < n; ++L) {
                for (int R = L; R < n; ++R) {
                    vector<int> block(cur.begin() + L, cur.begin() + R + 1);
                    vector<int> remain; remain.reserve(n - (R - L + 1));
                    remain.insert(remain.end(), cur.begin(), cur.begin() + L);
                    remain.insert(remain.end(), cur.begin() + R + 1, cur.end());
    
                    for (int ins = 0; ins <= (int)remain.size(); ++ins) {
                        vector<int> nxt; nxt.reserve(n);
                        nxt.insert(nxt.end(), remain.begin(), remain.begin() + ins);
                        nxt.insert(nxt.end(), block.begin(), block.end());
                        nxt.insert(nxt.end(), remain.begin() + ins, remain.end());
    
                        if (nxt == cur) continue;
                        if (dist.find(nxt) != dist.end()) continue;
    
                        dist[nxt] = d + 1;
                        if (nxt == nums2) return d + 1;
                        q.push(std::move(nxt));
                    }
                }
            }
        }
        return -1;
    }
};