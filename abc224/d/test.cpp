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
    int m;
    cin >> m;
    
    vector<vector<int>> g(10);
    rep(m){
        int u,v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    string s = "999999999";
    rep(i, 1, 9){
        int p;
        cin >> p;
        s[p-1] = i+'0';
    }

    queue<string> q;
    q.push(s);
    map<string, int> mp;
    mp[s] = 0;

    while(q.size()){
        auto now = q.front(); q.pop();
        int emp;
        rep(i, 1, 10){
            if(now[i-1] == '9') emp = i;
        }

        for(auto u: g[emp]){
            string t = now;
            swap(t[emp-1], t[u-1]);
            if(mp.count(t)) continue;
            mp[t] = mp[now] + 1;
            q.push(t);
        }
    }

    if(mp.count("123456789") == 0) cout << -1 << endl;
    else cout << mp["123456789"] << endl;
}   