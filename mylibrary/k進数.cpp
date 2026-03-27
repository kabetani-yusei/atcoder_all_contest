#include <bits/stdc++.h>
using namespace std;
#define ll long long

// 10進数をk進数に変える（kが10以下の場合）
string toBaseK(ll n, int k) {
    string result = "";
    while (n > 0) {
        int r = n % k;
        result = char('0' + r) + result;
        n /= k;
    }
    return result;
}

// k進数を10進数に変える（kが10以下の場合）
ll toDecimal(string s, int k) {
    ll result = 0;
    for (char c : s) {
        int digit = c - '0'; // '0'〜'9'前提
        result = result * k + digit;
    }
    return result;
}


/*
kが10より大きい場合
*/

// 10新しい数 -> k進数
string toBaseK(ll n, int k) {
    if (n == 0LL) return "0";

    string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result = "";

    while (n > 0) {
        int r = n % k;
        result = digits[r] + result;
        n /= k;
    }

    return result;
}

// k進数 -> 10進数
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