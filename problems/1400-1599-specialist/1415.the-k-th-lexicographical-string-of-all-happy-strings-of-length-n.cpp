class Solution {
public:
    void g(vector<string>& all, int n, string cur) {
        if(cur.size() == n) {
            all.push_back(cur);
            return;
        }
        for(char c : {'a', 'b', 'c'}) {
            if(cur.empty() || cur.back() != c) {
                g(all, n, cur + c);
            }
        }
    }
    string getHappyString(int n, int k) {
        vector<string> all;
        g(all, n, "");
        sort(all.begin(), all.end());
        if(k > all.size()) return "";
        else return all[k - 1];
    }
};
