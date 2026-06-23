#include <bits/stdc++.h>
using namespace std;
// #include <atcoder/all>
// using namespace atcoder;
// using mint = modint998244353;
#define ll long long
#define ull unsigned long long
const ll inf = 4'000'000'000'000'000'000LL; // 4e18
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


using P=pair<int,int>;

set<P> read_shape(int H, int W){
    set<P> res;
    rep(H){
        string s;
        cin >> s;
        rep(j, W){
            if(s[j] == '#'){
                res.insert({i,j});
            }
        }
    }
    return res;
}

set<P> shift_shape(const set<P>& s, int dx, int dy){
    set<P> res;
    for(auto [x, y] : s){
        res.insert({x + dx, y + dy});
    }
    return res;
}

set<P> norm_shape(set<P>& s){
    set<P> res;
    auto [mx, my] = *s.begin();
    for(auto [x,y]: s){
        res.insert({x-mx, y-my});
    }
    return res;
}

set<P> rotate90(set<P>& s){
    set<P> res;
    for(auto [x,y]: s){
        res.insert({y,-x});
    }
    return res;
}

bool in_range(const set<P>& s, int H, int W){
    for(auto [x, y] : s){
        if(x < 0 || x >= H || y < 0 || y >= W){
            return false;
        }
    }
    return true;
}

int main(){
    int HA, WA;
    cin >> HA >> WA;
    auto A = read_shape(HA, WA);

    int HB, WB;
    cin >> HB >> WB;
    auto B = read_shape(HB, WB);

    int HX, WX;
    cin >> HX >> WX;
    auto X = read_shape(HX, WX);

    for(int ax = -10; ax <= 10; ax++){
        for(int ay = -10; ay <= 10; ay++){
            for(int bx = -10; bx <= 10; bx++){
                for(int by = -10; by <= 10; by++){
                    auto SA = shift_shape(A, ax, ay);
                    auto SB = shift_shape(B, bx, by);

                    if(!in_range(SA, HX, WX)) continue;
                    if(!in_range(SB, HX, WX)) continue;

                    set<P> S = SA;
                    S.insert(all(SB));

                    if(S == X){
                        ouc("Yes");
                        return 0;
                    }
                }
            }
        }
    }
    ouc("No");
} 