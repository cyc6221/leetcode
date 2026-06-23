class Solution {
public:
    int minDeletion(string s, int k) {
        sort(s.begin(), s.end());
        vector<int> freq;
        for(int i=0; i<s.length(); i++) {
            int temp = 0;
            char c = s[i];
            while(i < s.length() && s[i] == c) {
                temp++;
                i++;
            }
            freq.push_back(temp);
            i--;
        }
        sort(freq.rbegin(), freq.rend());
        int res = 0;
        for(int i=k; i<freq.size(); i++) {
            res += freq[i];
        }
        return res;
    }
};
