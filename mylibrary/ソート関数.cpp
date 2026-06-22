#include <bits/stdc++.h>
using namespace std;
#define ll long long


int main() {
    vector<pair<int, int>> rectangles;
    for (int h = 1; h <= 150; ++h) {for (int w = h + 1; w <= 150; ++w) rectangles.push_back({h, w});}

    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        // aのほうが小さくなる（左にくる）場合にtrueとする
        int diagonalA = a.first * a.first + a.second * a.second;
        int diagonalB = b.first * b.first + b.second * b.second;
        if (diagonalA != diagonalB) {
            return diagonalA < diagonalB;
        }
        return a.first < b.first;
    };
    sort(rectangles.begin(), rectangles.end(), cmp);
    return 0;
}