# include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int distinctPoints(string s, int k) {
        set<vector<int>> g;

        int x = 0, y = 0;
        for(int i=k; i<s.size(); i++) {
            if(s[i] == 'U') y++;
            else if(s[i] == 'D') y--;
            else if(s[i] == 'L') x--;
            else if(s[i] == 'R') x++;
        }

        g.insert({x, y});

        for(int i=0, j=k; j<s.size(); i++, j++) {
            if(s[i] == 'U') y++;
            else if(s[i] == 'D') y--;
            else if(s[i] == 'L') x--;
            else if(s[i] == 'R') x++;

            if(s[j] == 'U') y--;
            else if(s[j] == 'D') y++;
            else if(s[j] == 'L') x++;
            else if(s[j] == 'R') x--;

            g.insert({x, y});
        }

        return g.size();
    }
};