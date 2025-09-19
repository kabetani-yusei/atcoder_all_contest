#include <bits/stdc++.h>
using namespace std;
// #include <atcoder/all>
// using namespace atcoder;
// using mint = modint998244353;
#define ll long long
#define ull unsigned long long
const ll minus_inf = -3e8;
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


int main(){
    int n,m;
    cin >> n >> m;
    vector<ll> h(n);
    rep(n) cin >> h[i];
    vector<vector<int>> edge(n);
    rep(m){
        int u,v;
        cin >> u >> v;
        u--; v--;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    priority_queue<pair<ll,int>> pq;
    vector<ll> used(n, 1e18);
    pq.push({0,0});
    used[0] = 0;
    ll ans=0;
    while(!pq.empty()){
        int now;
        now=pq.top().second;pq.pop();
        for(int next : edge[now]){
            ll diff;
            if(h[now] > h[next]){
                diff = 0;
            }else{
                diff = h[next] - h[now];
            }
            if(chmin(used[next], used[now] + diff)){
                chmax(ans, h[0] - h[next] - used[next]);
                pq.push({-used[next], next});
            }
        }
    }
    cout << ans << endl;
}   