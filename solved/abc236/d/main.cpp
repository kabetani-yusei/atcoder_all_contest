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

vector<vector<ll>> a;
ll n, ans = 0;

void dfs(vector<pair<int, int>> now, vector<int>& used) {
    if (now.size() == n) {
        ll sum = 0;
        rep(n) {
            sum ^= a[now[i].first][now[i].second];
        }
        chmax(ans, sum);
        return;
    }

    pair<int, int> p = {-1, -1};

    // 1つ目の要素
    rep(i, 2 * n) {
        if (used[i] == 0) {
            p.first = i;
            used[i] = 1;
            break;
        }
    }

    // 2つ目の要素
    rep(i, 2 * n) {
        if (used[i] == 0) {
            p.second = i;
            used[i] = 1;       // 2つ目の要素の選択
            now.push_back(p);  // 組み合わせを追加
            dfs(now, used);    // 再帰
            used[i] = 0;       // 2つ目の要素のリセット
            now.pop_back();    // 組み合わせを戻す
        }
    }

    // 1つ目の要素のリセット
    used[p.first] = 0;
}

int main() {
    cin >> n;
    a.resize(2 * n, vector<ll>(2 * n));
    rep(i, 2 * n - 1) {
        rep(j, i + 1, 2 * n) {
            cin >> a[i][j];
        }
    }

    vector<pair<int, int>> now;
    vector<int> used(2 * n, 0);

    dfs(now, used);

    cout << ans << endl;
}