#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
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

vector<vector<pair<int, int>>> g;
vector<int> c;

int dfs(int v, int pre, int goal){
    if(v == goal) return 1;
    for(auto [nv, i] : g[v]){
        if(nv == pre) continue;
        if(dfs(nv, v, goal)){
            c[i]++;
            return 1;
        }
    }
    return 0;
}

int main(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<int> a(m);
    rep(m){
        cin >> a[i];
        a[i]--;
    }
    g.resize(n);
    rep(n-1){
        int u,v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    c.resize(n-1);
    rep(m-1) dfs(a[i], -1, a[i+1]);

    int s=0;
    rep(n-1) s+=c[i];
    if((s+k)%2 || s+k < 0){
        cout << 0 << endl;
        return 0;
    }

    vector<mint> dp(100001);
    dp[0] = 1;
    rep(i, n-1){
        for(int j=100000; j>= c[i]; j--){
            dp[j] += dp[j-c[i]];
        }
    }
    cout << dp[(s+k)/2].val() << endl;
}   