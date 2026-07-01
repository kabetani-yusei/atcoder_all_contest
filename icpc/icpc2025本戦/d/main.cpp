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

vector<pair<char,int>> runLengthEncoding(const string& s){
    vector<pair<char,int>> res;
    for(char c : s){
        if(res.empty() || res.back().first != c){
            res.push_back({c,1});
        }else{
            res.back().second++;
        }
    }
    return res;
}

bool valid(vector<pair<char,int>> res, int cnt){
    int nr = (int)res.size();
    rep(i,1,nr-1){
        if(cnt != res[i].second){
            return false;
        }
    }
    if(res[0].second>cnt || res[nr-1].second>cnt){
        return false;
    }
    return true;
}

bool solve() {
    int n,m;
    cin >> n >> m;
    if(n == 0 && m == 0){
        return false;
    }
    /*
    #.
    .#
    の形を探す
    ある -> そこから伸びていくやつで幅を全探索
    ない -> 圧縮して矛盾check
    */
    int x = -1, y = -1;
    vector<string> c(n);
    rep(n) cin >> c[i];
    rep(n-1){
        rep(j,m-1){
            string check = {c[i][j], c[i][j+1], c[i+1][j], c[i+1][j+1]};
            int cnt = 0;
            for(auto ci: check){
                if(ci == '#') cnt++;
            }
            if(cnt%2 != 0){
                ouc(-1);
                return true;
            }else if(check == "#..#" || check == ".##."){
                x = i, y = j;
                break;
            }
        }
    }
    if(x != -1){
        int ans = -1;
        string check = {c[x][y], c[x][y+1]};
        rep(k, 1, 120){
            bool ok = true;
            rep(n){
                rep(j,m){
                    int xx = i+(k-1-x)+100*k, yy = j+(k-1-y)+100*k;
                    if(c[i][j] != check[(xx/k)%2 ^ (yy/k)%2]){
                        ok = false;
                        break;
                    }
                }
            }
            if(ok){
                if(ans == -1){
                    ans = k;
                }else{
                    ouc(0);
                    return true;
                }
            }
        }
        if(ans == -1){
            ouc(-1);
        }else{
            ouc(ans);
        }
    }else{
        string t;
        rep(n){
            t.push_back(c[i][0]);
        }
        auto res1 = runLengthEncoding(c[0]);
        auto res2 = runLengthEncoding(t);
        
        int cnt = 0;
        if((int)res1.size()>=3){
            cnt = res1[1].second;
        }
        if((int)res2.size()>=3){
            if(cnt == 0){
                cnt = res2[1].second;
            }else if(cnt != res2[1].second){
                ouc(-1);
                return true;
            }
        }
        if(cnt!=0 && (!valid(res1,cnt) || !valid(res2,cnt))){
            ouc(-1);
            return true;
        }
        ouc(cnt);
    }
    return true;
}

int main() {
    while(solve());
    return 0;
}