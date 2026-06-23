class Solution {
public:
    int minSwaps(string s) {
        int res = 0, cur = 0;
        for(int i=0; i<s.size(); i++) {
            if(s[i] == '[') cur++;
            else {
                if(cur > 0) cur--;
                else {
                    res++;
                    cur = 1;
                }
            }
        }
        return res;
    }
};
