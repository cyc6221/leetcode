struct RMQ {
    int n, LOG;
    vector<int> lg;                 // floor(log2(i))
    vector<vector<int>> stMax;      // stMax[k][i] = max on [i, i+2^k-1]
    vector<vector<int>> stMin;      // stMin[k][i] = min on [i, i+2^k-1]

    RMQ() {}
    RMQ(const vector<int>& a) { build(a); }

    void build(const vector<int>& a) {
        n = (int)a.size();
        LOG = 1;
        while ((1 << LOG) <= n) ++LOG;

        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

        stMax.assign(LOG, vector<int>(n));
        stMin.assign(LOG, vector<int>(n));
        // k = 0
        for (int i = 0; i < n; ++i) {
            stMax[0][i] = a[i];
            stMin[0][i] = a[i];
        }
        // k > 0
        for (int k = 1; k < LOG; ++k) {
            int len = 1 << k;
            int half = len >> 1;
            for (int i = 0; i + len - 1 < n; ++i) {
                stMax[k][i] = std::max(stMax[k - 1][i], stMax[k - 1][i + half]);
                stMin[k][i] = std::min(stMin[k - 1][i], stMin[k - 1][i + half]);
            }
        }
    }

    inline int rangeMax(int l, int r) const {
        if (l > r) swap(l, r);
        int k = lg[r - l + 1];
        return std::max(stMax[k][l], stMax[k][r - (1 << k) + 1]);
    }
    inline int rangeMin(int l, int r) const {
        if (l > r) swap(l, r);
        int k = lg[r - l + 1];
        return std::min(stMin[k][l], stMin[k][r - (1 << k) + 1]);
    }
    inline int value(int l, int r) const { // v(l,r) = max - min
        return rangeMax(l, r) - rangeMin(l, r);
    }
};

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = (int)nums.size();
        RMQ rmq(nums);

        // 對每個固定 l，序列 v(l, r)（r 往左移）為非增
        // 初始化將 (l, r = n-1) 放入最大堆
        using Node = pair<int, pair<int,int>>; // (value, (l, r))
        priority_queue<Node> pq;
        pq = priority_queue<Node>();

        for (int l = 0; l < n; ++l) {
            int r = n - 1;
            int v = rmq.value(l, r);
            pq.push({v, {l, r}});
        }

        long long ans = 0;
        while (k-- > 0 && !pq.empty()) {
            auto [val, lr] = pq.top(); pq.pop();
            int l = lr.first, r = lr.second;
            ans += (long long)val;

            // 往同一 row 的下一個（r-1）推進
            if (r > l) {
                int nr = r - 1;
                int nv = rmq.value(l, nr);
                pq.push({nv, {l, nr}});
            }
        }
        return ans;
    }
};