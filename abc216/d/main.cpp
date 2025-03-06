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


int main(){
    int n,m;
    cin >> n >> m;
    vector<int> k(m), s(n+1, -1), cnt(m, 0);
    vector<vector<int>> a(m);
    deque<pair<int,int>> q;
    rep(m){
        cin >> k[i];
        a[i].resize(k[i]);
        rep(j,k[i]) cin >> a[i][j];
        q.push_back({a[i][0], i});
    }

    int ans = 0;
    while(q.size()){
        auto [x, y] = q.front();
        q.pop_front();
        if(s[x] != -1){
            ans++;
            cnt[y]++;
            if(cnt[y] < k[y]){
                q.push_back({a[y][cnt[y]], y});
            }
            cnt[s[x]]++;
            if(cnt[s[x]] < k[s[x]]){
                q.push_back({a[s[x]][cnt[s[x]]], s[x]});
            }
        }else{
            s[x] = y;
        }
    }
    cout << (ans == n ? "Yes" : "No") << endl;
}   