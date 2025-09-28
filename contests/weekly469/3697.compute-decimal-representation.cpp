class Solution {
public:
    vector<int> decimalRepresentation(int n) {
        vector<int> res;
        long long p = 1;
        while(n > 0) {
            int cur = p * (n % 10);
            if(cur > 0) res.push_back(cur);
            p *= 10;
            n /= 10;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};