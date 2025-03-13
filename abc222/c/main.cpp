#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
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


int main(){
    int n,mm;
    cin >> n >> mm;
    vector<string> a(2 * n);
    rep(2 * n) cin >> a[i];
    vector<pair<int, int>> rank(2*n);
    rep(2*n) rank[i] = {0, i};
    rep(m,mm){
        rep(n){
            if(a[rank[2*i].second][m] == 'G'){
                if(a[rank[2*i+1].second][m] == 'C') rank[2*i].first++;
                else if(a[rank[2*i+1].second][m] == 'P') rank[2*i+1].first++;
            }else if(a[rank[2*i].second][m] == 'C'){
                if(a[rank[2*i+1].second][m] == 'P') rank[2*i].first++;
                else if(a[rank[2*i+1].second][m] == 'G') rank[2*i+1].first++;
            }else{
                if(a[rank[2*i+1].second][m] == 'G') rank[2*i].first++;
                else if(a[rank[2*i+1].second][m] == 'C') rank[2*i+1].first++;
            }
        }
        sort(all(rank), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) 
                return a.first > b.first; // 1つ目の要素を降順
            return a.second < b.second;   // 2つ目の要素を昇順
        });
    }
    rep(2*n) cout << rank[i].second + 1 << endl;
}   