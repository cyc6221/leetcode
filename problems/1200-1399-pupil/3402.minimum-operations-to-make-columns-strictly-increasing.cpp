class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int res = 0;
        for(int j=0; j < grid[0].size(); j++) {
            int prev = grid[0][j];
            for(int i=1; i < grid.size(); i++) {
                if(prev >= grid[i][j]) {
                    res += prev - grid[i][j] + 1;
                    prev++;
                }
                prev = max(prev, grid[i][j]);
            }
        }
        return res;
    }
};
