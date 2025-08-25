class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& q) {
        long long res = 0;
        map<int, multiset<int>> mp;
        for(int i=0; i<q.size(); i++) {
            long long l = q[i][0];
            long long r = q[i][1];
            long long k = q[i][2];
            long long v = q[i][3];
            while(l <= r) {
                // long long temp = nums[l];
                // temp *= v;
                // temp %= 1000000007;
                // nums[l] = temp;
                mp[l].insert(v);
                l += k;
            }
        }
        for(auto& i : mp) {
            int l = i.first;
            multiset<int> s = i.second;
            long long temp = 1;
            for(auto& j : s) {
                if(s.count(j) % 2 == 1) {
                    temp *= j;
                    temp %= 1000000007;
                }
            }
            // cout << temp << endl;
            temp = temp * nums[l];
            temp %= 1000000007;
            nums[l] = temp;
        }
        for(auto& i : nums) res ^= i;
        return res;
    }
};

// NOT FINISHED