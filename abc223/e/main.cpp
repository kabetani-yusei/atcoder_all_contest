#include <bits/stdc++.h>
using namespace std;
// #include <atcoder/all>
// using namespace atcoder;
// using mint = modint998244353;
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

bool check(ll x, ll y, ll a, ll b, ll c){
    bool ans = false;
    ll now = (a + x-1) / x;
    ll k = y - now;
    if(k > 0){
        now = (b + k-1) / k + (c + k-1) / k;
        if(now <= x) ans = true;
    }
    return ans;
}

int main(){
    ll x,y,a,b,c;
    cin >> x >> y >> a >> b >> c;
    bool ans = false;
    // 縦に3つ
    ll now = (a + x-1) / x + (b + x-1) / x + (c + x-1) / x;
    if(now <= y) ans = true;
    // 横に3つ
    now = (a + y-1) / y + (b + y-1) / y + (c + y-1) / y;
    if(now <= x) ans = true;
    // 縦に1つ横に2つ
    if(check(x,y,a,b,c)) ans = true;
    if(check(x,y,b,c,a)) ans = true;
    if(check(x,y,c,a,b)) ans = true;
    // 縦に2つ横に1つ
    if(check(y,x,a,b,c)) ans = true;
    if(check(y,x,b,c,a)) ans = true;
    if(check(y,x,c,a,b)) ans = true;
    cout << (ans ? "Yes" : "No") << endl;
}   