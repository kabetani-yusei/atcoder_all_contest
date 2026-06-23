#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 有向グラフの閉路検出
bool hasCycleDirected(vector<vector<int>>& g) {
    int n = g.size();
    // 0: 未訪問, 1: 探索中, 2: 探索済み
    vector<int> state(n, 0);
    auto dfs = [&](auto self, int v) -> bool {
        state[v] = 1; // 探索中
        for (auto nv : g[v]) {
            if (state[nv] == 1) {
                // 探索中の頂点に戻ったので閉路あり
                return true;
            }
            if (state[nv] == 0) {
                if (self(self, nv)) return true;
            }
        }
        state[v] = 2; // 探索済み
        return false;
    };
    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            if (dfs(dfs, i)) return true;
        }
    }
    return false;
}



// 無向グラフの閉路検出
bool hasCycleUndirected(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> seen(n, 0);
    auto dfs = [&](auto self, int v, int parent) -> bool {
        seen[v] = 1;
        bool skipped_parent = false;
        for (auto nv : g[v]) {
            if (nv == parent && !skipped_parent) {
                skipped_parent = true;
                continue;
            }
            if (seen[nv]) return true;
            if (self(self, nv, v)) return true;
        }
        return false;
    };
    for (int i = 0; i < n; i++) {
        if (!seen[i]) {
            if (dfs(dfs, i, -1)) return true;
        }
    }
    return false;
}
