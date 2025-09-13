class Solution {
public:
    int minArrivalsToDiscard(vector<int>& arrivals, int w, int m) {
        int res = 0;
        unordered_map<int, int> mp;
        vector<int> kpt(arrivals.size(), 1);
        for(int i=0; i<arrivals.size(); i++) {
            if(i-w >= 0 && kpt[i-w]) {
                mp[arrivals[i-w]]--;
            }
            mp[arrivals[i]]++;
            // cout << mp[3] << endl;
            // if(i >= w) {
            if(mp[arrivals[i]] > m) {
                mp[arrivals[i]]--;
                res++;
                kpt[i] = 0;
            }
            // }
        }
        return res;
    }
};