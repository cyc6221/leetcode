/*
 * @lc app=leetcode id=3608 lang=cpp
 *
 * [3608] Minimum Time for K Connected Components
 *
 * https://leetcode.com/problems/minimum-time-for-k-connected-components/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * You are given an integer n and an undirected graph with n nodes labeled from
 * 0 to n - 1. This is represented by a 2D array edges, where edges[i] = [ui,
 * vi, timei] indicates an undirected edge between nodes ui and vi that can be
 * removed at timei.
 * 
 * You are also given an integer k.
 * 
 * Initially, the graph may be connected or disconnected. Your task is to find
 * the minimum time t such that after removing all edges with time <= t, the
 * graph contains at least k connected components.
 * 
 * Return the minimum time t.
 * 
 * A connected component is a subgraph of a graph in which there exists a path
 * between any two vertices, and no vertex of the subgraph shares an edge with
 * a vertex outside of the subgraph.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 2, edges = [[0,1,3]], k = 2
 * 
 * Output: 3
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Initially, there is one connected component {0, 1}.
 * At time = 1 or 2, the graph remains unchanged.
 * At time = 3, edge [0, 1] is removed, resulting in k = 2 connected components
 * {0}, {1}. Thus, the answer is 3.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 3, edges = [[0,1,2],[1,2,4]], k = 3
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Initially, there is one connected component {0, 1, 2}.
 * At time = 2, edge [0, 1] is removed, resulting in two connected components
 * {0}, {1, 2}.
 * At time = 4, edge [1, 2] is removed, resulting in k = 3 connected components
 * {0}, {1}, {2}. Thus, the answer is 4.
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 3, edges = [[0,2,5]], k = 2
 * 
 * Output: 0
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Since there are already k = 2 disconnected components {1}, {0, 2}, no edge
 * removal is needed. Thus, the answer is 0.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 10^5
 * 0 <= edges.length <= 10^5
 * edges[i] = [ui, vi, timei]
 * 0 <= ui, vi < n
 * ui != vi
 * 1 <= timei <= 10^9
 * 1 <= k <= n
 * There are no duplicate edges.
 * 
 * 
 */

// @lc code=start
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
/* --- */
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
            // unite(uf, u, v);
            // if(count_components(uf) < k) {
            //     return edges[i][2];
            // }
        }
        return 0;
    }
};
// @lc code=end

