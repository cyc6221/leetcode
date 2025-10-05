class Solution {
public:
    string removeSubstring(string s, int k) {
        vector<pair<char, int>> runs;

        auto try_merge_last_two = [&]() {
            if (runs.size() >= 2 && runs[runs.size()-1].first == runs[runs.size()-2].first) {
                runs[runs.size()-2].second += runs.back().second;
                runs.pop_back();
            }
        };

        auto try_reduce_tail = [&]() {
            while (runs.size() >= 2 &&
                   runs[runs.size()-2].first == '(' &&
                   runs[runs.size()-1].first == ')' &&
                   runs[runs.size()-2].second >= k &&
                   runs[runs.size()-1].second >= k) {
    
                runs[runs.size()-2].second -= k;
                runs[runs.size()-1].second -= k;
    
                if (runs.back().second == 0) runs.pop_back();
                if (!runs.empty() && runs.back().second == 0) runs.pop_back();
    
                try_merge_last_two();
            }
        };

        for(char & c : s) {
            if(!runs.empty() && runs.back().first == c) {
                runs.back().second++;
            }
            else {
                runs.emplace_back(c, 1);
            }
            try_reduce_tail();
        }

        string res;
        for(auto &p : runs) res.append(p.second, p.first);
        return res;
    }
};
