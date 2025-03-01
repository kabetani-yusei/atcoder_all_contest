#include <bits/stdc++.h>
using namespace std;
#define ll long long
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


int main(){
    int h,w;
    cin >> h >> w;
    vector<vector<int>> s(h, vector<int>(w));
    rep(h) rep(j,w){
        char c;
        cin >> c;
        s[i][j] = c == '#' ? 1 : 0;
    }
    vector<vector<int>> used(h, vector<int>(w, 1e9));
    deque<pair<int,int>> q;
    q.push_back({0,0});
    used[0][0] = 0;
    while(q.size()){
        auto now = q.front();
        q.pop_front();
        // 通常の移動で行ける
        rep(i,4){
            int nx = now.first + dx[i];
            int ny = now.second + dy[i];
            if(nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
            if(s[nx][ny] == 1){
                continue;
            }else{
                if(chmin(used[nx][ny], used[now.first][now.second])){
                    q.push_front({nx,ny});
                }
            }
        }
        // パンチをすると行ける
        rep(i,-3,3) rep(j,-3,3){
            if(abs(i) + abs(j) > 3) continue;
            int nx = now.first + i;
            int ny = now.second + j;
            if(nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
            if(chmin(used[nx][ny], used[now.first][now.second] + 1)){
                q.push_back({nx,ny});
            }
        }
    }
    cout << used[h-1][w-1] << endl;
}   