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
    vector<int> c(n);
    rep(n) cin >> c[i];
    if(n==1){
        ouc("Yes");
        cout << c[0] << endl;
        return true;
    }else if(n==2){
        if(c[0] != c[1]){
            ouc("No");
        }else{
            ouc("Yes");
            cout << c[0] << " " << c[1] << endl;
            cout << c[0] << " " << c[1] << endl;
        }
        return true;
    }
    int fi=-1, se=n;
    rep(i,n){
        if(c[i]==c[0]) chmax(fi, i);
        if(c[i]==c[n-1]) chmin(se,i);
    }
    if(fi==-1 || se==n || fi < se){
        ouc("No");
        return true;
    }
    vector ans(n, vector<int>(n, 0));
    // ある方向を決めて、回転していく
    rep(k,4){
        vector<vector<int>> tmp = ans;
        rep(n){
            rep(j,n){
                tmp[i][j] = ans[n-1-j][i];
            }
        }
        ans = tmp;
        // front
        rep(i,se,fi+1){
            ans[n-1][i] = c[i];
        }
        // seの上
        rrep(i,fi+1,n){
            ans[i][se] = c[i];
        }
        // fiの上
        rep(i,0,se){
            ans[n-1-i][fi] = c[i];
        }
    }
    ouc("Yes");
    rep(n){
        rep(j,n){
            if(j != n-1) cout << ans[i][j] << " ";
            else cout << ans[i][j] << endl;
        }
    }
    return true;
}

int main() {
    while(solve());
    return 0;
}