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

string vec_int_to_str(vector<int> a){
    string s = "";
    for(int x : a) s += to_string(x);
    return s;
}


int main(){
    int m;
    cin >> m;
    vector<pair<int, int>> edge(m);
    rep(m){
        cin >> edge[i].first >> edge[i].second;
        edge[i].first--;
        edge[i].second--;
    }
    vector<int> s(9), p(8);
    rep(9) s[i] = i;
    rep(8){
        cin >> p[i];
        p[i]--;
    }

    string start = vec_int_to_str(p) + 'a';
    string goal = vec_int_to_str(s);
    set<string> st;
    queue<pair<string, int>> q;
    q.push({start, 0});
    while(!q.empty()){
        auto [now, cnt] = q.front();
        q.pop();
        bool check = true;
        rep(9){
            if(now[i] != 'a' && now[i] != goal[i]){
                check = false;
                break;
            }
        }
        if(check){
            cout << cnt << endl;
            return 0;
        }
        rep(m){
            if(now[edge[i].first] != 'a' && now[edge[i].second] != 'a') continue;
            string next = now;
            swap(next[edge[i].first], next[edge[i].second]);
            if(st.count(next)) continue;
            st.insert(next);
            q.push({next, cnt + 1});
        }
    }
    cout << -1 << endl;
}   