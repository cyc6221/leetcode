// UPSOLVING

class Solution {
public:
    int double_chars(string s, char x, char y) {
        int n = s.size();
        int res = 0;
        unordered_map<int, int> first;
        int bal = 0;

        first[0] = -1;

        for(int i=0; i<n; i++) {
            if(s[i] == x) bal++;
            else if(s[i] == y) bal--;
            else {
                bal = 0;
                first.clear();
                first[0] = i;
                continue;
            }
            if(first.count(bal)) {
                res = max(res, i - first[bal]);
            }
            else {
                first[bal] = i;
            }
        }
        return res;
    }
    int longestBalanced(string s) {
        int res = 0;
        int n = s.size();

        // single char
        char ch = s[0];
        for(int i=0, cur=0; i<n; i++) {
            if(s[i] == ch) {
                cur++;
            }
            else {
                ch = s[i];
                cur = 1;
            }
            res = max(res, cur);
        }

        // double chars
        res = max(res, double_chars(s, 'a', 'b'));
        res = max(res, double_chars(s, 'b', 'c'));
        res = max(res, double_chars(s, 'a', 'c'));

        // triple chars
        int a=0, b=0, c=0;
        map<pair<int, int>, int> mp;
        mp[{0,0}] = -1;

        for(int i=0; i<n; i++) {
            if(s[i] == 'a') a++;
            else if(s[i] == 'b') b++;
            else if(s[i] == 'c') c++;

            pair<int, int> k = {a - b, a - c};
            if(mp.count(k)) res = max(res, i - mp[k]);
            else mp[k] = i;
        }

        return res;
    }
};