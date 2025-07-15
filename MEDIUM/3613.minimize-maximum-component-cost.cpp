/*
 * @lc app=leetcode id=3613 lang=cpp
 *
 * [3613] Minimize Maximum Component Cost
 *
 * https://leetcode.com/problems/minimize-maximum-component-cost/description/
 *
 * Category: algorithms
 * Difficulty: Medium
 *
 * You are given an undirected connected graph with n nodes labeled from 0 to n
 * - 1 and a 2D integer array edges where edges[i] = [ui, vi, wi] denotes an
 * undirected edge between node ui and node vi with weight wi, and an integer
 * k.
 * 
 * You are allowed to remove any number of edges from the graph such that the
 * resulting graph has at most k connected components.
 * 
 * The cost of a component is defined as the maximum edge weight in that
 * component. If a component has no edges, its cost is 0.
 * 
 * Return the minimum possible value of the maximum cost among all components
 * after such removals.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: n = 5, edges = [[0,1,4],[1,2,3],[1,3,2],[3,4,6]], k = 2
 * 
 * Output: 4
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * Remove the edge between nodes 3 and 4 (weight 6).
 * The resulting components have costs of 0 and 4, so the overall maximum cost
 * is 4.
 * 
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: n = 4, edges = [[0,1,5],[1,2,5],[2,3,5]], k = 1
 * 
 * Output: 5
 * 
 * Explanation:
 * 
 * 
 * 
 * 
 * No edge can be removed, since allowing only one component (k = 1) requires
 * the graph to stay fully connected.
 * That single component’s cost equals its largest edge weight, which is
 * 5.
 * 
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= n <= 5 * 10^4
 * 0 <= edges.length <= 10^5
 * edges[i].length == 3
 * 0 <= ui, vi < n
 * 1 <= wi <= 10^6
 * 1 <= k <= n
 * The input graph is connected.
 * 
 * 
 */

// @lc code=start
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
// @lc code=end

