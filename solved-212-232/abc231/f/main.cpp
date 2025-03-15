#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
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

int op(int a, int b){ return a + b; }
int e(){ return 0; }

int comp(vector<int> &A){
    std::map<int,int> mem;
    for(auto p: A) mem[p] = 0;
    int sz = 0;
    for(auto &p: mem) p.second = sz++;
    for(auto &p: A) p = mem[p];
    return sz;
}

int main(){
    int n;
    cin >> n;
    vector<pair<int, int>> aa(n);
    rep(n) cin >> aa[i].first;
    rep(n) cin >> aa[i].second;
    sort(all(aa), [](auto a, auto b){ 
        if(a.first == b.first) return a.second > b.second;
        return a.first < b.first; 
    });
    vector<int> a(n), b(n);
    rep(n){
        a[i] = aa[i].first;
        b[i] = aa[i].second;
    }
    int bb = comp(b);
    segtree<int, op, e> seg(bb);
    ll ans = 0;
    int cnt = 0;
    rep(n){
        if(i != 0 && a[i] == a[i - 1] && b[i] == b[i - 1]){
            seg.set(b[i], seg.prod(b[i], b[i] + 1) + 1);
            ans += seg.prod(b[i], bb);
            cnt++;
        }else{
            ans += (ll)cnt * (cnt + 1) / 2;
            cnt = 0;
            seg.set(b[i], seg.prod(b[i], b[i] + 1) + 1);
            ans += seg.prod(b[i], bb);
        }
    }
    ans += (ll)cnt * (cnt + 1) / 2; 
    cout << ans << endl;
}   