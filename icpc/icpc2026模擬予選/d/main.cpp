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

int ans = 0;

bool ng_check(vector<pair<int,int>>& tmp){
    rep(4){
        rep(j,i+1,4){
            int l1 = tmp[i].first, l2 = tmp[j].first;
            int r1 = tmp[i].second, r2 = tmp[j].second;
            if(max(l1,l2) <= min(r1,r2)){
                return true;
            }
        }
    }
    return false;
}

void dfs(int n, int pa, int key, int now, vector<pair<int,int>> vp, vector<set<vector<int>>>& sides){
    if(key >= n){
        return;
    }
    if((pa & (1<<key))==0){
        return dfs(n,pa,key+1,now,vp,sides);
    }
    now += 1;
    for(auto ssi: sides[key]){
        vector<pair<int,int>> tmp = vp;
        rep(j, 4){
            if(vp[0].first == -1){
                tmp[j].first = ssi[j];
                tmp[j].second = ssi[j];
            }else{
                chmin(tmp[j].first, ssi[j]);
                chmax(tmp[j].second, ssi[j]);
            }
        }
        if(ng_check(tmp)){
            continue;
        }
        chmax(ans, now);
        dfs(n,pa,key+1,now,tmp,sides);
    }
    return;
}

vector<int> rotate_side(vector<int> a){
    auto res = a;
    rep(3){
        // 左回転　rotate(a.begin(), a.begin() + 1, a.end());
        rotate(a.begin(), a.end() - 1, a.end()); // 右回転
        chmin(res, a);
    }
    return res;
}

bool solve() {
    int n;
    cin >> n;
    if(n == 0){
        return false;
    }
    vector<vector<int>> boxes(n, vector<int>(6));
    rep(n){
        rep(j,6) cin >> boxes[i][j];
    }
    // 側面の管理
    vector<set<vector<int>>> sides(n);
    rep(box_type, n){
        vector<vector<int>> side_types = {
            {0,2,1,3},
            {0,3,1,2},
            {0,5,1,4},
            {0,4,1,5},
            {2,4,3,5},
            {2,5,3,4}
        };
        for(auto &sidet: side_types){
            vector<int> c;
            rep(j,4){
                c.push_back(boxes[box_type][sidet[j]]);
            }
            sides[box_type].insert(rotate_side(c));
        }
    }
    // bit全探索
    ans = 0;
    for(int i=0; i<(1<<n); i++){
        vector<pair<int,int>> vp(4, {-1,-1});
        dfs(n,i,0,0,vp,sides);
    }
    ouc(ans);
    return true;
}

int main() {
    while(solve());
    return 0;
}