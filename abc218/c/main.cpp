#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;
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

pair<int,int> left_top(vector<string> &s){
    int n = s.size();
    rep(i, n){
        rep(j, n){
            if(s[i][j] == '#'){
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

int main(){
    int n;
    cin >> n;
    vector<string> s(n);
    rep(n) cin >> s[i];
    vector<string> t(n);
    rep(n) cin >> t[i];
    int s_num=0, t_num=0;
    rep(n){
        rep(j, n){
            if(s[i][j] == '#') s_num++;
            if(t[i][j] == '#') t_num++;
        }
    }
    if(s_num != t_num){
        cout << "No" << '\n';
        return 0;
    }
    //左上にそろえればよさそう
    //sの左上の位置
    int s_x, s_y;
    tie(s_x, s_y) = left_top(s);
    // 回転-> sとtが一致するか
    rep(tt, 4){
        int t_x, t_y, dx, dy, cnt=0;
        tie(t_x, t_y) = left_top(t);
        dx = t_x - s_x;
        dy = t_y - s_y;
        rep(i, n){
            rep(j, n){
                if(0 <= i + dx && i + dx < n && 0 <= j + dy && j + dy < n){
                    if(s[i][j] == '#' && s[i][j] == t[i + dx][j + dy]){
                        cnt += 1;
                    }
                }
            }
        }
        if(cnt == s_num){
            cout << "Yes" << '\n';
            return 0;
        }
        //90度回転
        vector<string> tmp(n, string(n, '.'));
        rep(i, n){
            rep(j, n){
                tmp[j][n - 1 - i] = t[i][j];
            }
        }
        t = tmp;
    }
    cout << "No" << '\n';
}   