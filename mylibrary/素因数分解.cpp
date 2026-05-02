#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ユークリッドの互除法
ll gcd(ll a, ll b) {
    while(a) {
        ll tmp = a;
        a = b % a;
        b = tmp;
    }
    return b;
}

// 愚直な素因数分解
vector<ll> pfact(ll x){
    vector<ll> res;
    for(ll i=2;i<=x/i;i++){
        while(x%i==0){
            x/=i;
            res.push_back(i);
        }
    }
    if(x!=1){res.push_back(x);}
    return res;
}

// 線形篩
// maxp以下の素数リストを返す
vector<ll> prime_list;
void construct_plist(ll maxp) {
    if (maxp < 2) {
        prime_list.clear();
        return;
    }
    maxp++;
    vector<bool> is_prime(maxp, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i < maxp; i++) {
        if (is_prime[i]) {
            prime_list.push_back(i);
        }
        for (int j = 0; j < (int)prime_list.size(); j++) {
            ll p = prime_list[j];
            if (i * p >= maxp) break;

            is_prime[i * p] = false;

            if (i % p == 0) break;
        }
    }
}


/*

ここからは高速に素因数分解するやつ

*/

// オーバーフロー対策のため __int128 を用いた乗算 (mod 演算付き)
ll modmul(ll a, ll b, ll mod) {
    return (__int128)a * b % mod;
}

// 繰り返し二乗法による高速な mod 累乗
ll modpow(ll base, ll exp, ll mod) {
    ll result = 1 % mod;
    base %= mod;
    while(exp > 0) {
        if(exp & 1)
            result = modmul(result, base, mod);
        base = modmul(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// Miller-Rabin 法による素数判定
bool is_prime(ll n) {
    if(n == 2) return true;
    if(n == 1 || n % 2 == 0) return false;
    ll m = n - 1;
    // m = 2^s * d とする．lsb は m の最下位ビット (2 の累乗部分)
    ll lsb = m & -m;
    int s = __builtin_ctzll(lsb);  // lsb = 2^s であるため，s を取得
    ll d = m / lsb;
    
    vector<ll> test_numbers = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for(ll a : test_numbers) {
        if(a == n) continue;
        ll x = modpow(a, d, n);
        if(x == 1) continue;
        int r = 0;
        while(x != m) {
            x = modmul(x, x, n);
            r++;
            if(x == 1 || r == s)
                return false;
        }
    }
    return true;
}

// Pollard-Rho 法を用いて n の素因数を 1 つ求める
ll find_prime_factor(ll n) {
    if(n % 2 == 0)
        return 2;
    
    // m = floor(n^(1/8)) + 1
    ll m = (ll)pow((long double)n, 0.125) + 1;
    
    for (ll c = 1; c < n; c++) {
        auto f = [n, c](ll a) -> ll {
            return (modmul(a, a, n) + c) % n;
        };
        ll y = 0;
        ll g = 1, q = 1, r = 1;
        ll k = 0;
        ll x, ys = 0;
        while(g == 1) {
            x = y;
            while(k < (3 * r) / 4) {
                y = f(y);
                k++;
            }
            while(k < r && g == 1) {
                ys = y;
                ll loop = min(m, r - k);
                for(ll i = 0; i < loop; i++){
                    y = f(y);
                    ll diff = (x > y ? x - y : y - x);
                    q = modmul(q, diff, n);
                }
                g = gcd(q, n);
                k += m;
            }
            k = r;
            r *= 2;
        }
        if(g == n) {
            g = 1;
            y = ys;
            while(g == 1) {
                y = f(y);
                ll diff = (x > y ? x - y : y - x);
                g = gcd(diff, n);
            }
        }
        if(g == n)
            continue;
        if(is_prime(g))
            return g;
        else if(is_prime(n / g))
            return n / g;
        else
            return find_prime_factor(g);
    }
    return n;
}

// 素因数分解：結果を map (素因数, 指数) として返す
map<ll, ll> factorize(ll n) {
    map<ll, ll> res;
    while(n > 1 && !is_prime(n)) {
        ll p = find_prime_factor(n);
        ll s = 0;
        while(n % p == 0) {
            n /= p;
            s++;
        }
        res[p] += s;
    }
    if(n > 1)
        res[n] = 1;
    return res;
}
