/*
 * @lc app=leetcode id=3600 lang=cpp
 *
 * [3600] Maximize Spanning Tree Stability with Upgrades
 *
 * https://leetcode.com/problems/maximize-spanning-tree-stability-with-upgrades/description/
 *
 * Category: algorithms
 * Difficulty: Hard
 *
 * You are given an integer n, representing n nodes numbered from 0 to n - 1
 * and a list of edges, where edges[i] = [ui, vi, si, musti]:
 * 
 * 
 * ui and vi indicates an undirected edge between nodes ui and vi.
 * si is the strength of the edge.
 * musti is an integer (0 or 1). If musti == 1, the edge must be included in
 * the spanning tree. These edges cannot be upgraded.
 * 
 * 
 * You are also given an integer k, the maximum number of upgrades you can
 * perform. Each upgrade doubles the strength of an edge, and each eligible
 * edge (with musti == 0) can be upgraded at most once.
 * 
 * The stability of a spanning tree is defined as the minimum strength score
 * among all edges included in it.
 * 
 * Return the maximum possible stability of any valid spanning tree. If it is
 * impossible to connect all nodes, return -1.
 * 
 * Note: A spanning tree of a graph with n nodes is a subset of the edges that
 * connects all nodes together (i.e. the graph is connected) without forming
 * any cycles, and uses exactly n - 1 edges.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 3, edges = [[0,1,2,1],[1,2,3,0]], k = 1
 * 
 * Output: 2
 * 
 * Explanation:
 * 
 * 
 * Edge [0,1] with strength = 2 must be included in the spanning tree.
 * Edge [1,2] is optional and can be upgraded from 3 to 6 using one
 * upgrade.
 * The resulting spanning tree includes these two edges with strengths 2 and
 * 6.
 * The minimum strength in the spanning tree is 2, which is the maximum
 * possible stability.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 3, edges = [[0,1,4,0],[1,2,3,0],[0,2,1,0]], k = 2
 * 
 * Output: 6
 * 
 * Explanation:
 * 
 * 
 * Since all edges are optional and up to k = 2 upgrades are allowed.
 * Upgrade edges [0,1] from 4 to 8 and [1,2] from 3 to 6.
 * The resulting spanning tree includes these two edges with strengths 8 and
 * 6.
 * The minimum strength in the tree is 6, which is the maximum possible
 * stability.
 * 
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: n = 3, edges = [[0,1,1,1],[1,2,1,1],[2,0,1,1]], k = 0
 * 
 * Output: -1
 * 
 * Explanation:
 * 
 * 
 * All edges are mandatory and form a cycle, which violates the spanning tree
 * property of acyclicity. Thus, the answer is -1.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 2 <= n <= 10^5
 * 1 <= edges.length <= 10^5
 * edges[i] = [ui, vi, si, musti]
 * 0 <= ui, vi < n
 * ui != vi
 * 1 <= si <= 10^5
 * musti is either 0 or 1.
 * 0 <= k <= n
 * There are no duplicate edges.
 * 
 * 
 */

// @lc code=start
class Solution {
public:

    // Union-Find
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
    // Union-Find


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
// @lc code=end

