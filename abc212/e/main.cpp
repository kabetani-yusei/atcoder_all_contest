#include <bits/stdc++.h>
using namespace std;
#define ll long long
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

const ll mod = 998244353;

int main(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<pair<int, int>> edge;
    rep(m){
        int a,b;
        cin >> a >> b;
        a--; b--;
        edge.push_back({a,b});
    }
    vector<vector<ll>> dp(k+1, vector<ll>(n, 0));
    dp[0][0] = 1;
    rep(ii,1,k+1){
        ll sum = 0;
        rep(jj,n){
            sum += dp[ii-1][jj];
            sum %= mod;
        }
        rep(jj,n){
            dp[ii][jj] = sum + mod - dp[ii-1][jj];
            dp[ii][jj] %= mod;
        }
        rep(kk,m){
            int a,b;
            tie(a,b) = edge[kk];
            dp[ii][b] += mod - dp[ii-1][a];
            dp[ii][b] %= mod;
            dp[ii][a] += mod - dp[ii-1][b];
            dp[ii][a] %= mod;
        }
    }
    cout << dp[k][0] << endl;
}   