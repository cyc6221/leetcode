class Solution {
public:
    using ll = long long;

    bool back(ll Sum, ll cur, vector<ll>& res) {
        if(Sum == 0) {
            return true;
        }

        for(ll i = cur; i <= Sum; i += 2) {
            if(!res.empty() && i < res.back()) break;
            res.push_back(i);
            if(back(Sum - i, i + 2, res)) {
                return true;
            }

            res.pop_back();
        }
        return false;
    }

    vector<ll> maximumEvenSplit(ll finalSum) {
        vector<ll> res;
        if(finalSum % 2 != 0) return res;
        back(finalSum, 2, res);
        return res;
    }
};
