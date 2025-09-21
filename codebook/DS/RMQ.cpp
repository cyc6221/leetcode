// ===================== Sparse Table (Value) =====================
// 靜態 RMQ：O(n log n) 預處理，O(1) 區間查詢 [l, r]（含）
// 適用於 idempotent 且可結合的運算：min/max/gcd/bitwise_and/or 等
// 例：SparseTable<int, MinOp> st(a);  st.query(l, r);

struct MinOp { template<class T> T operator()(const T& a, const T& b) const { return a < b ? a : b; } };
struct MaxOp { template<class T> T operator()(const T& a, const T& b) const { return a > b ? a : b; } };
struct GcdOp {
    template<class T> T operator()(T a, T b) const {
        if (a == 0) return b; if (b == 0) return a;
        while (b) { T t = a % b; a = b; b = t; }
        return a;
    }
};

template <class T, class Op>
struct SparseTable {
    int n, LOG;
    Op op;
    std::vector<int> lg;              // floor(log2(i))
    std::vector<std::vector<T>> st;   // st[k][i]: 長度 2^k, 起點 i 的聚合值

    SparseTable() : n(0), LOG(0) {}
    SparseTable(const std::vector<T>& a, Op op = Op()) : op(op) { build(a); }

    void build(const std::vector<T>& a) {
        n = (int)a.size();
        LOG = 1; while ((1 << LOG) <= n) ++LOG;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

        st.assign(LOG, std::vector<T>(n));
        // k = 0
        for (int i = 0; i < n; ++i) st[0][i] = a[i];
        // k > 0
        for (int k = 1; k < LOG; ++k) {
            int len = 1 << k, half = len >> 1;
            for (int i = 0; i + len - 1 < n; ++i) {
                st[k][i] = op(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }

    // 查詢 [l, r]（含）。若 l > r 會自動交換。
    T query(int l, int r) const {
        if (l > r) std::swap(l, r);
        int k = lg[r - l + 1];
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
// vector<int> a = {...};
// SparseTable<int, MinOp> stMin(a);
// SparseTable<int, MaxOp> stMax(a);
// int mn = stMin.query(l, r);
// int mx = stMax.query(l, r);
// int g  = SparseTable<int, GcdOp>(a).query(l, r);


// ===================== Sparse Table (Index: argmin/argmax) =====================
// 回傳極值「位置」：O(n log n) 預處理，O(1) 查詢 [l, r]（含）
// Comp(a[i], a[j]) 應返回 true 當 i 的值「比較好」（較小 or 較大）
// 例：ArgMin 使用：SparseTableIdx<int, std::less<int>> stIdx(a);
//     int pos = stIdx.arg_query(l, r);  int val = a[pos];

template<class T>
struct LessEq { bool operator()(const T& a, const T& b) const { return a < b || (!(b < a)); } }; // a <= b（含穩定）

template <class T, class Comp = std::less<T>>
struct SparseTableIdx {
    int n, LOG;
    const std::vector<T>* arr;
    Comp cmp;
    std::vector<int> lg;
    std::vector<std::vector<int>> st; // st[k][i] = 在 [i, i+2^k-1] 的最佳索引

    SparseTableIdx() : n(0), LOG(0), arr(nullptr) {}
    SparseTableIdx(const std::vector<T>& a, Comp cmp = Comp()) : arr(&a), cmp(cmp) { build(a); }

    void build(const std::vector<T>& a) {
        arr = &a;
        n = (int)a.size();
        LOG = 1; while ((1 << LOG) <= n) ++LOG;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

        st.assign(LOG, std::vector<int>(n));
        for (int i = 0; i < n; ++i) st[0][i] = i;

        auto better = [&](int i, int j) {
            if (i == -1) return true;
            if (j == -1) return false;
            // 若 a[i] 與 a[j] 相等，選較小索引以穩定
            if (!cmp((*arr)[j], (*arr)[i]) && !cmp((*arr)[i], (*arr)[j])) return i < j;
            return cmp((*arr)[i], (*arr)[j]);
        };

        for (int k = 1; k < LOG; ++k) {
            int len = 1 << k, half = len >> 1;
            for (int i = 0; i + len - 1 < n; ++i) {
                int L = st[k - 1][i];
                int R = st[k - 1][i + half];
                st[k][i] = better(L, R) ? L : R;
            }
        }
    }

    // 回傳 [l, r]（含）內的最佳索引；若 l > r 會自動交換。
    int arg_query(int l, int r) const {
        if (l > r) std::swap(l, r);
        int k = lg[r - l + 1];
        int i = st[k][l];
        int j = st[k][r - (1 << k) + 1];
        // 比較 i, j 兩個候選，回傳較佳者（相等值選較小索引）
        if (!cmp((*arr)[j], (*arr)[i]) && !cmp((*arr)[i], (*arr)[j])) return std::min(i, j);
        return cmp((*arr)[i], (*arr)[j]) ? i : j;
    }
};
// vector<int> a = {...};

// Argmin（最小值位置）
// SparseTableIdx<int, std::less<int>> stArgMin(a);
// int pmin = stArgMin.arg_query(l, r); // a[pmin] 是最小值（相等取較小索引)

// Argmax（最大值位置）
// SparseTableIdx<int, std::greater<int>> stArgMax(a);
// int pmax = stArgMax.arg_query(l, r); // a[pmax] 是最大值（相等取較小索引)
