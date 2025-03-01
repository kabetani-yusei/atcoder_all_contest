#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;
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
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    rep(i,n) a[i] = s[i] - 'A';
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(1<<10, vector<ll>(10,0)));
    rep(i,n) dp[i][1 << a[i]][a[i]] = 1;
    rep(i,n-1){
        rep(j, 1<<10){
            rep(k, 10){
                dp[i+1][j][k] += dp[i][j][k];
                dp[i+1][j][k] %= mod;
            }
            if(j & 1 << a[i+1]){
                dp[i+1][j][a[i+1]] += dp[i][j][a[i+1]];
                dp[i+1][j][a[i+1]] %= mod;
            }else{
                rep(k,10){
                    dp[i+1][j | 1 << a[i+1]][a[i+1]] += dp[i][j][k];
                    dp[i+1][j | 1 << a[i+1]][a[i+1]] %= mod;
                }
            }
        }
    }
    ll ans = 0;
    rep(j,1,1<<10){
        rep(k,10){
            ans += dp[n-1][j][k];
            ans %= mod;
        }
    }
    cout << ans << '\n';
}   