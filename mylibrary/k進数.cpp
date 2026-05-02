#include <bits/stdc++.h>
using namespace std;
#define ll long long

// 10進数をK進数に変換する
string toBaseK(ll n, int k) {
    if (n == 0) return "0";
    string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result = "";

    while (n > 0) {
        result = digits[n % k] + result;
        n /= k;
    }
    return result;
}

// K進数を10進数に変換する
int charToInt(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'Z') return c - 'A' + 10;
    return -1;
}
ll toDecimal(string s, int k) {
    ll result = 0;
    for (char c : s) {
        int digit = charToInt(c);
        result = result * k + digit;
    }
    return result;
}