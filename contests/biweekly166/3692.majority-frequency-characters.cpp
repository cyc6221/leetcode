# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string majorityFrequencyGroup(string s) {
        vector<int> arr(26, 0);
        for(int i=0; i<s.size(); i++) {
            arr[s[i] - 'a']++;
        }
        
        unordered_map<char, int> mp;
        for(int i=0; i<26; i++) {
            if (arr[i] > 0) mp[arr[i]]++;
        }

        int bestK = 0;
        int bestSize = -1;
        for (const auto &p : mp) {
            int k = p.first, sz = p.second;
            if (sz > bestSize || (sz == bestSize && k > bestK)) {
                bestSize = sz;
                bestK = k;
            }
        }

        string ans;
        for (int i = 0; i < 26; ++i) {
            if (arr[i] == bestK) ans.push_back('a' + i);
        }
        return ans;
    }
};