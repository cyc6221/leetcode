class Solution {
public:
    long long perfectPairs(vector<int>& nums) {
        long long res = 0;
        vector<long long> pos;
        for(auto& i : nums) {
            if(i == 0) res++;
            else pos.push_back(abs(i));
        }
        
        res = res * (res - 1) / 2;
        sort(pos.begin(), pos.end());

        int l=0, r=0;
        for(r-0; r<pos.size(); r++) {
            while(l < r && pos[l] * 2 < pos[r]) l++;
            res += (r - l);
        }
        return res;
    }
};