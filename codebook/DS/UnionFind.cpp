// unionfind.cpp
// Disjoint Set Union (DSU) / Union-Find
// Supports: initialization, find root with path compression, union by size, connectivity check, and component size query.

#include <vector>
using namespace std;

// Initializes the union-find structure with n elements (0-based)
void init_union_find(vector<int>& uf, int n) {
    uf.assign(n, -1);  // -1 means root and size 1
}

// Finds the root of x with path compression
int find(vector<int>& uf, int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf, uf[x]);
}

// Unites the sets containing x and y
// Returns true if merged, false if already in the same set
bool unite(vector<int>& uf, int x, int y) {
    x = find(uf, x);
    y = find(uf, y);
    if (x == y) return false;

    // Union by size: merge smaller set into larger one
    if (uf[x] > uf[y]) swap(x, y);
    uf[x] += uf[y];  // update size
    uf[y] = x;       // make x the new root
    return true;
}

// Returns true if x and y are in the same set
bool connected(vector<int>& uf, int x, int y) {
    return find(uf, x) == find(uf, y);
}

// Returns the size of the set containing x
int size(vector<int>& uf, int x) {
    return -uf[find(uf, x)];
}

// Count how many connected components (distinct sets) are currently in the structure
int count_components(const vector<int>& uf) {
    int count = 0;
    for (int i = 0; i < uf.size(); ++i) {
        if (uf[i] < 0) ++count; // Root node of a component
    }
    return count;
}


/*
Usage example:

#include "unionfind.cpp"

int main() {
    int n = 5;
    vector<int> uf;
    init_union_find(uf, n);

    unite(uf, 0, 1);
    unite(uf, 1, 2);

    if (connected(uf, 0, 2)) {
        // 0 and 2 are in the same set
    }

    int sz = size(uf, 0);  // sz = 3
}
*/

/* COPY HERE */

void init_union_find(vector<int>& uf, int n) {
    uf.assign(n, -1);
}
int find(vector<int>& uf, int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf, uf[x]);
}
bool unite(vector<int>& uf, int x, int y) {
    x = find(uf, x);
    y = find(uf, y);
    if (x == y) return false;

    if (uf[x] > uf[y]) swap(x, y);
    uf[x] += uf[y];
    uf[y] = x;
    return true;
}
bool connected(vector<int>& uf, int x, int y) {
    return find(uf, x) == find(uf, y);
}
int size(vector<int>& uf, int x) {
    return -uf[find(uf, x)];
}
int count_components(const vector<int>& uf) {
    int count = 0;
    for (int i = 0; i < uf.size(); ++i) {
        if (uf[i] < 0) ++count;
    }
    return count;
}
