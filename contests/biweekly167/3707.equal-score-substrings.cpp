class Solution {
public:
    bool scoreBalance(string s) {
        int all = 0;
        for(auto& i : s) {
            all += (i - 'a') + 1;
        }
        int half = 0;
        for(auto& i : s) {
            half += (i - 'a') + 1;
            if(half == all - half) return true;
        }
        return false;
    }
};