class Solution {
public:
    string res;

    bool repeat(string& s, string &pat, int k) {
        if(pat.empty()) return true;

        int cnt = 0, pos = 0;

        for(char c : s) {
            if(c == pat[pos]) {
                pos = (pos + 1) % pat.length();
                if(pos == 0) {
                    cnt++;
                    if(cnt == k) return true;
                }
            }
        }
        return false;
    }

    void back(string& s, int k, string cur) {
        if(cur.length() >= res.length()) {
            res = max(res, cur);

        }

        for (char c = 'a'; c <= 'z'; c++) {
            cur.push_back(c);
            if(repeat(s, cur, k)) back(s, k, cur);
            cur.pop_back();
        }
    }

    string longestSubsequenceRepeatedK(string s, int k) {
        vector<int> cnt(26, 0);
        for(char c : s) {
            cnt[c - 'a']++;
        }
        string temp;
        for(char c : s) {
            if(cnt[c - 'a'] >= k) {
                temp += c;
            }
        }
        s = temp;
        res = "";
        back(s, k, res);
        return res;
    }
};
