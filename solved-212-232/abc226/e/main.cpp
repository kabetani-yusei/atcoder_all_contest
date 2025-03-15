#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define ull unsigned long long
const ll inf = 1e18;
const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
const int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
#define bsearch(a,x) distance(a.begin(), lower_bound(all(a), x))
#define all(a) a.begin(),a.end()
#define overload(_1,_2,_3,_4,name,...) name
#define _rep1(n) for(int i = 0; i < (n); i++)
#define _rep2(i,n) for(int i = 0; i < (n); i++)
#define _rep3(i,a,b) for(int i = (a); i < (b); i++)
#define _rep4(i,a,b,c) for(int i = (a); i < (b); i += (c))
#define rep(...) overload(__VA_ARGS__,_rep4,_rep3,_rep2,_rep1)(__VA_ARGS__)
#define _rrep1(n) for(int i = (n) - 1; i >= 0; i--)
#define _rrep2(i,n) for(int i = (n) - 1; i >= 0; i--)
#define _rrep3(i,a,b) for(int i = (b) - 1; i >= (a); i--)
#define _rrep4(i,a,b,c) for(int i = (b) - 1; i >= (a); i -= (c))
#define rrep(...) overload(__VA_ARGS__,_rrep4,_rrep3,_rrep2,_rrep1)(__VA_ARGS__)
template <class T> bool chmin(T& a, T b){ if(a > b){ a = b; return 1; } return 0; }
template <class T> bool chmax(T& a, T b){ if(a < b){ a = b; return 1; } return 0; }
struct Edge { int to; ll cost; Edge(int to, ll cost) : to(to), cost(cost) {} };
using Graph = vector<vector<Edge>>;
// cout << fixed << setprecision(15);

void dfs(int now, vector<vector<int>> &g, vector<bool> &visited){
    visited[now] = true;
    for(int next : g[now]){
        if(visited[next]) continue;
        dfs(next, g, visited);
    }
}

int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    rep(m){
        int u,v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // ng_check
    if(n != m){
        cout << 0 << endl;
        return 0;
    }

    vector<int> used(n, false);
    rep(n){
        if(used[i] == false && g[i].size() == 0){
            cout << 0 << endl;
            return 0;
        }else if(g[i].size() == 1){
            used[i] = true;
            queue<int> q;
            q.push(i);
            while(!q.empty()){
                int now = q.front();
                used[now] = true;
                q.pop();
                int next = g[now][0];
                g[now].clear();
                g[next].erase(remove(all(g[next]), now), g[next].end());
                if(g[next].size() == 1){
                    q.push(next);
                }else if (g[next].size() == 0){
                    cout << 0 << endl;
                    return 0;
                }
            }
        }
    }

    // ループを数える
    vector<bool> visited(n, false);
    mint ans = 1;
    rep(n){
        if(used[i] || visited[i]) continue;
        dfs(i, g, visited);
        ans *= 2;
    }
    cout << ans.val() << endl;
}   