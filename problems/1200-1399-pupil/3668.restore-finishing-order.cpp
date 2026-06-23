class Solution {
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        vector<int> res;
        for(auto& i : order) {
            if(find(friends.begin(), friends.end(), i) != friends.end()) res.push_back(i);
        }
        return res;
    }
};