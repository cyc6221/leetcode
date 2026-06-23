class Solution {
public:
    int getLeastFrequentDigit(int n) {
        map<int, int> mp;
        while(n > 0) {
            mp[n % 10] ++;
            n /= 10;
        }

        int res = -1, cnt = INT_MAX;
        for(auto& i : mp) {
            if(i.second < cnt) {
                res = i.first;
                cnt = i.second;
            }
            else if(i.second == cnt) res = min(res, i.first);
        }
        return res;
    }
};