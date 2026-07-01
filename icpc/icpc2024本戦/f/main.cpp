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
// void ouc(auto a){cout << a << '\n';}
// void yesno(bool b){ouc(b ? "Yes" : "No");}
// cout << fixed << setprecision(15);

const int DX[4] = { 1,  1, -1, -1};
const int DY[4] = { 1, -1, -1,  1};

bool solve() {
    int W, H, CX, CY, N;
    cin >> W >> H >> CX >> CY >> N;

    if (W == 0 && H == 0 && CX == 0 && CY == 0 && N == 0) {
        return false;
    }

    vector<int> X(N), Y(N);

    // plus[s]  : x + y = s の直線上にある球
    // minus[d] : x - y = d - H の直線上にある球
    vector<vector<pair<int, int>>> plus(W + H + 1);
    vector<vector<pair<int, int>>> minus(W + H + 1);

    for (int i = 0; i < N; i++) {
        cin >> X[i] >> Y[i];

        plus[X[i] + Y[i]].push_back({X[i], i});
        minus[X[i] - Y[i] + H].push_back({X[i], i});
    }

    for (auto &v : plus) sort(v.begin(), v.end());
    for (auto &v : minus) sort(v.begin(), v.end());

    vector<bool> ok(N, false);

    auto next_state = [&](int x, int y, int d) {
        int vx = DX[d];
        int vy = DY[d];

        int tx = (vx == 1 ? W - x : x);
        int ty = (vy == 1 ? H - y : y);

        int t = min(tx, ty);

        int nx = x + vx * t;
        int ny = y + vy * t;

        bool hit_x = (nx == 0 || nx == W);
        bool hit_y = (ny == 0 || ny == H);

        int nd = d;

        // 角に着いたら穴に落ちるので終了
        if (hit_x && hit_y) {
            nd = -1;
        } else {
            // 縦の壁に当たったら左右反転
            if (hit_x) nd ^= 3;

            // 横の壁に当たったら上下反転
            if (hit_y) nd ^= 1;
        }

        return tuple<int, int, int>(nx, ny, nd);
    };

    auto get_balls = [&](int x, int y, int nx, int ny, int d, int limit) {
        vector<int> res;
        (void)ny;

        const vector<pair<int, int>> *vec;

        if (d == 0 || d == 2) {
            // ↗ / ↙ は x - y が一定
            vec = &minus[x - y + H];
        } else {
            // ↘ / ↖ は x + y が一定
            vec = &plus[x + y];
        }

        const auto &v = *vec;

        if (d == 0 || d == 1) {
            // x が増える方向
            int L = x + 1;
            int R = nx;

            auto it = lower_bound(v.begin(), v.end(), pair<int, int>{L, -1});

            while (it != v.end() && it->first <= R) {
                res.push_back(it->second);
                if ((int)res.size() == limit) break;
                ++it;
            }
        } else {
            // x が減る方向
            int L = nx;
            int R = x - 1;

            auto it = upper_bound(v.begin(), v.end(), pair<int, int>{R, INT_MAX});

            while (it != v.begin()) {
                --it;

                if (it->first < L) break;

                res.push_back(it->second);
                if ((int)res.size() == limit) break;
            }
        }

        return res;
    };

    int g = gcd(W, H);

    // 反射状態は周期的なので、これ以上見れば十分
    ll LIMIT = 2LL * (W / g + H / g) + 10;

    for (int start_d = 0; start_d < 4; start_d++) {
        int x = CX;
        int y = CY;
        int d = start_d;

        // 途中で出会った球
        // -1 なら、まだ球に出会っていない
        int seen = -1;

        for (ll step = 0; step < LIMIT; step++) {
            auto [nx, ny, nd] = next_state(x, y, d);

            if (d == 2) {
                // 逆向きで ↙ に進んでいる
                // この方向で球に当たるなら、元向きではその球を ↗ に突ける
                auto balls = get_balls(x, y, nx, ny, d, 1);

                if (!balls.empty()) {
                    int cand = balls[0];

                    // ここまで何も球に会っていない
                    // または、会った球が cand 自身だけなら OK
                    if (seen == -1 || seen == cand) {
                        ok[cand] = true;
                    }

                    break;
                }
            } else {
                // ↙ 以外で見つけた球は、候補ではない
                // ただし、後で候補自身だったと分かる可能性があるので seen に記録する
                auto balls = get_balls(x, y, nx, ny, d, 2);

                bool bad = false;

                for (int id : balls) {
                    if (seen == -1) {
                        seen = id;
                    } else if (seen != id) {
                        // 途中で別の球に出会った
                        // 元向きではコインより前にこの球に当たるので失敗
                        bad = true;
                        break;
                    }
                }

                if (bad) break;
            }

            // 穴に落ちた
            if (nd == -1) break;

            x = nx;
            y = ny;
            d = nd;
        }
    }

    vector<int> ans;
    for (int i = 0; i < N; i++) {
        if (ok[i]) ans.push_back(i + 1);
    }

    if (ans.empty()) {
        cout << "No\n";
    } else {
        for (int x : ans) {
            cout << x << ' ';
        }
        cout << '\n';
    }
    return true;
}

int main() {
    while(solve());
    return 0;
}