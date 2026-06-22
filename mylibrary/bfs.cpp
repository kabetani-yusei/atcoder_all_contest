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
void ouc(auto a){cout << a << '\n';}
void yesno(bool b){ouc(b ? "Yes" : "No");}
// cout << fixed << setprecision(15);


int main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    rep(m){
        int u,v;
        cin >> u >> v;
        u--;v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<int> que;
    vector<int> seen(n,-1);
    que.push(0);
    seen[0] = 0;
    while(!que.empty()){
        int now = que.front();
        que.pop();
        for(auto nex: g[now]){
            if(seen[nex]==-1 || seen[nex] > seen[now]+1){
                seen[nex] = seen[now]+1;
                que.push(nex);
            }
        }
    }
    /*
    // 2次元座標の場合
    queue<pair<int,int>> que;
    vector<vector<int>> seen(h, vector<int>(w, -1));
    que.push(s);
    seen[s.first][s.second] = 0;
    while (!que.empty()) {
        auto [x, y] = que.front();
        que.pop();
        rep(k, 4) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (0 <= nx && nx < h && 0 <= ny && ny < w && (seen[nx][ny] == -1 || seen[nx][ny] > seen[x][y] + 1)) {
                seen[nx][ny] = seen[x][y] + 1;
                que.push({nx, ny});
            }
        }
    }
    */
}   