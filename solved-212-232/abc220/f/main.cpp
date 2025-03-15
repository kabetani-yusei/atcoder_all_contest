#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;
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

pair<int, ll> dp[200005]={{0,0}};
ll ans[200005] = {0};

pair<int, ll> dfs(int pos, vector<vector<int>>& edge){
    dp[pos] = {1, 0};
    for(auto i : edge[pos]){
        if(dp[i].first != 0) continue;
        auto res = dfs(i, edge);
        dp[pos].first += res.first;
        dp[pos].second += res.first + res.second;
    }
    return dp[pos];
}

 void dfs2(int pos, vector<vector<int>>& edge){
    int n = edge.size();
    for(auto i : edge[pos]){
        if(ans[i] > 0) continue;
        ans[i] = ans[pos] - dp[i].first + (n-dp[i].first);
        dfs2(i, edge);
    }
}

int main(){
    int n;
    cin >> n;
    vector<vector<int>> edge(n);
    rep(n-1){
        int v,w;
        cin >> v >> w;
        v--; w--;
        edge[v].push_back(w);
        edge[w].push_back(v);
    }
    int now = 0;
    rep(n){
        if(edge[i].size() == 1){
            now = i;
            break;
        }
    }
    dfs(now, edge);
    ans[now] = dp[now].second;
    dfs2(now, edge);
    rep(n){
        cout << ans[i] << '\n';
    }
}   