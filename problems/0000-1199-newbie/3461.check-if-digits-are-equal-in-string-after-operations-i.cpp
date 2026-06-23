class Solution {
public:
    bool hasSameDigits(string s) {
        if(s.length() == 2) {
            return s[0] == s[1];
        }
        string next;
        for(int i=0; i<s.length()-1; i++) {
            next += to_string((s[i] - '0' + s[i+1] - '0') % 10);
        }
        return hasSameDigits(next);
    }
};
