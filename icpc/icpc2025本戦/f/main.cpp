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
    string s,t;
    cin >> s >> t;
    string tmp1 = s, tmp2 = t;
    sort(all(tmp1));
    sort(all(tmp2));
    if(tmp1 != tmp2){
        ouc("no");
        return true;
    }
    int acnt = 0, bcnt = 0;
    rep(n){
        if(s[i]=='a'){
            acnt++;
        }else{
            bcnt++;
        }
    }
    string ans;

    // step1: bが最後にくる形を作る（aa,...,aabbb,...,bb）
    rep(acnt){
        if(s[i]!='a'){
            rep(j,i,acnt){
                ans.push_back('B');
            }
            break;
        }
    }
    bool type = 0; // 0->bが最後、1->aが最後
    rrep(n){
        if(t[i]=='a'){
            if(type == 0){
                rep(bcnt){
                    ans.push_back('A');
                }
                type = 1;
            }
            acnt--;
        }else{
            if(type == 1){
                rep(acnt){
                    ans.push_back('B');
                }
                type = 0;
            }
            bcnt--;
        }
    }
    ouc("yes");
    ouc(ans);
    return true;
}

int main() {
    while(solve());
    return 0;
}