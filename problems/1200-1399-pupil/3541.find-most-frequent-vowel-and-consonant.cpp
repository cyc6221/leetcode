class Solution {
public:
    int maxFreqSum(string s) {
        unordered_map<char, int> ump;
        for(auto& i : s) ump[i] ++;

        int res1 = 0, res2 = 0;
        for(auto& i : ump) {
            if(i.first == 'a') res1 = max(res1, i.second);
            else if(i.first == 'e') res1 = max(res1, i.second);
            else if(i.first == 'i') res1 = max(res1, i.second);
            else if(i.first == 'o') res1 = max(res1, i.second);
            else if(i.first == 'u') res1 = max(res1, i.second);
            else res2 = max(res2, i.second);
        }
        return res1 + res2;
    }
};
