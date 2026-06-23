class Solution {
public:
    int min_unfairness = INT_MAX;

    void dis(vector<int>& cookies, int k, int i_cook, vector<int>& child) {
        if(i_cook == cookies.size()) {
            int max_cookies = 0;
            for(int i = 0; i < k; i++) {
                max_cookies = max(max_cookies, child[i]);
            }
            min_unfairness = min(min_unfairness, max_cookies);
            return;
        }

        for(int i = 0; i < k; i++) {
            child[i] += cookies[i_cook];
            dis(cookies, k, i_cook + 1, child);
            child[i] -= cookies[i_cook];
        }
    }

    int distributeCookies(vector<int>& cookies, int k) {
        vector<int> child(k, 0);
        min_unfairness = INT_MAX;
        dis(cookies, k, 0, child);
        return min_unfairness;
    }
};
