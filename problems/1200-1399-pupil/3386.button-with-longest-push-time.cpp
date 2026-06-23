class Solution {
public:
    int buttonWithLongestTime(vector<vector<int>>& events) {
        map<int, int> mp;
        for(int i=0; i<events.size(); i++) {
            if(i == 0) {
                mp[events[i][0]] = events[i][1];
            } else {
                mp[events[i][0]] = max(mp[events[i][0]], events[i][1] - events[i-1][1]);
            }
        }
        int res = 0;
        int maxTime = 0;
        for(auto& [key, value] : mp) {
            if(value > maxTime) {
                maxTime = value;
                res = key;
            } else if(value == maxTime) {
                res = min(res, key);
            }
        }
        return res;
    }
};
