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

const ll SCALE = 1000000000LL;
const ll DEG180 = 180LL * SCALE;
const ll DEG360 = 360LL * SCALE;

ll parse_angle(string s) {
    int p = s.find('.');
    ll integer = stoll(s.substr(0, p));
    string frac = s.substr(p + 1);

    while ((int)frac.size() < 9) frac.push_back('0');

    return integer * SCALE + stoll(frac);
}

ll norm_angle(ll x) {
    x %= DEG360;
    if (x < 0) x += DEG360;
    return x;
}

vector<ll> make_dirs(const vector<ll>& angle) {
    int n = angle.size();

    vector<ll> dirs;
    ll cur = 0;
    dirs.push_back(cur);

    rep(n-1){
        ll exterior = DEG180 - angle[i];
        cur = norm_angle(cur + exterior);
        dirs.push_back(cur);
    }

    return dirs;
}

bool solve() {
    int n;
    cin >> n;
    if(n == 0){
        return false;
    }
    vector<ll> a(n);
    rep(n){
        string s;
        cin >> s;
        a[i] = parse_angle(s);
    }

    int m;
    cin >> m;
    vector<ll> b(m);
    rep(m){
        string s;
        cin >> s;
        b[i] = parse_angle(s);
    }

    vector<ll> p = make_dirs(a);
    vector<ll> q = make_dirs(b);

    unordered_set<ll> P;
    for (ll x : p) P.insert(x);

    set<int> faces;

    // k = 0 は必ず可能
    faces.insert(2 + n + m);

    // q[j] を p[i] に合わせる回転を全部試す
    for (ll x : p) {
        for (ll y : q) {
            ll rot = norm_angle(x - y);

            int k = 0;
            for (ll v : q) {
                ll nv = norm_angle(v + rot);
                if (P.count(nv)) k++;
            }

            faces.insert(2 + n + m - k);
        }
    }

    bool first = true;
    for (int f : faces) {
        if(!first) cout << " ";
        first = false;
        cout << f;
    }
    cout << endl;
    return true;
}

int main() {
    while(solve());
    return 0;
}