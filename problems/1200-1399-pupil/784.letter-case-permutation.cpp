class Solution {
public:
    void dfs(vector<string>& res, string &s, int i, string &cur) {
        if(i == s.length()) {
            res.push_back(cur);
            return;
        }

        int a = s[i] - 'a', A = s[i] - 'A';
        if(A >= 0 && A < 26) s[i] = A + 'a', a = A;

        cur.push_back(s[i]);
        dfs(res, s, i+1, cur);
        cur.pop_back();

        if(a >= 0 && a < 26) {
            cur.push_back(a + 'A');
            dfs(res, s, i+1, cur);
            cur.pop_back();
        }
    }
    vector<string> letterCasePermutation(string s) {
        vector<string> res;
        string cur = "";
        dfs(res, s, 0, cur);
        return res;
    }
};
