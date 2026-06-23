class Solution {
public:
    int back(vector<int>& cnt) {
        int res = 0;
        for(int i=0; i < 26; i++) {
            if(cnt[i] > 0) {
                cnt[i]--;
                res += 1 + back(cnt);
                cnt[i]++;
            }
        }
        return res;
    }
    int numTilePossibilities(string tiles) {
        vector<int> cnt(26, 0);
        for(char c : tiles) {
            cnt[c - 'A']++;
        }

        return back(cnt);
    }
};
