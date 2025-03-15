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
// cout << fixed << setprecision(15);


int main(){
    ll n,a,b;
    cin >> n >> a >> b;
    ll p,q,r,s;
    cin >> p >> q >> r >> s;
    ll k1,k2,k3,k4;
    k1 = max(1-a, 1-b);
    k2 = min(n-a, n-b);
    k3 = max(1-a, b-n);
    k4 = min(n-a, b-1);
    for(ll i=p; i<=q; i++){
        for(ll j=r; j<=s; j++){
            bool flag = false;
            //条件1
            ll kk1 = i-a, kk2 = j-b;
            if(kk1 == kk2 && k1 <= kk1 && kk1 <= k2){
                flag = true;
            }
            //条件2
            kk1 = i-a, kk2 = b-j;
            if(kk1 == kk2 && k3 <= kk1 && kk1 <= k4){
                flag = true;
            }
            cout << (flag ? '#' : '.');
        }
        cout << endl;
    }
}   