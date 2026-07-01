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

bool solve() {
    int n;
    cin >> n;
    if(n == 0){
        return false;
    }
    vector<int> p(n+1), e(n+1);
    rep(i,2,n+1){
        cin >> p[i] >> e[i];
    }
    vector<vector<pair<int,int>>> g(n+1);
    rep(i,2,n+1){
        g[p[i]].push_back({i,e[i]});
        g[i].push_back({p[i],e[i]});
    }

    // 頂点への重みづけ
    vector<int> v_w(n+1);
    vector<pair<int,int>> t_w;

    queue<int> que;
    vector<int> seen(n+1,-1);
    que.push(1);
    seen[1] = 0;
    while(!que.empty()){
        int now = que.front();
        que.pop();
        for(auto nexi: g[now]){
            auto [nex, ww] = nexi;
            if(seen[nex]==-1 || seen[nex] > seen[now]+1){
                seen[nex] = seen[now]+1;
                v_w[nex] = ww;
                t_w.push_back({ww, nex});
                que.push(nex);
            }
        }
    }
    sort(all(t_w));

    vector<int> ans;
    vector<bool> used(n+1, false);
    used[1] = true;
    for(auto tti: t_w){
        auto [wi, vi] = tti;
        if(used[vi]) continue;
        vector<int> tmp;
        int now = vi;
        while(used[now] == false){
            tmp.push_back(now);
            used[now] = true;
            for(auto nexi: g[now]){
                auto nex = nexi.first;
                if(seen[nex] == seen[now]-1){
                    now = nex;
                    break;
                }
            }
        }
        reverse(all(tmp));
        for(auto ti: tmp) ans.push_back(ti);
    }

    rep(i,n-1){
        if(i > v_w[ans[i]]){
            ouc("no");
            return true;
        }
    }
    ouc("yes");
    for(auto ansi: ans){
        if(ansi == ans[n-2]) cout << ansi << endl;
        else cout << ansi << " ";
    }
    return true;
}

int main() {
    while(solve());
    return 0;
}