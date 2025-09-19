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


int main(){
    ll h,w,k;
    cin >> h >> w >> k;
    ll x1,y1,x2,y2;
    cin >> x1 >> y1 >> x2 >> y2;
    mint a1=1, a2=0, a3=0, a4=0;
    rep(k){
        mint ta1=a1.val(), ta2=a2.val(), ta3=a3.val(), ta4=a4.val();
        a1 = (w-1)*ta2 + (h-1)*ta3;
        a2 = (w-2)*ta2 + (h-1)*ta4 + ta1;
        a3 = (h-2)*ta3 + (w-1)*ta4 + ta1;
        a4 = ta2 + ta3 + (w-2+h-2)*ta4;
    }
    if(x2==x1 && y2==y1){
        cout << a1.val() << endl;
        return 0;
    }else if(x2==x1){
        cout << a2.val() << endl;
        return 0;
    }else if(y2==y1){
        cout << a3.val() << endl;
        return 0;
    }else{
        cout << a4.val() << endl;
        return 0;
    }
}   