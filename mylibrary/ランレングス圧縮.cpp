#include <bits/stdc++.h>
using namespace std;

vector<pair<char,int>> runLengthEncoding(const string& s){
    vector<pair<char,int>> res;
    for(char c : s){
        if(res.empty() || res.back().first != c){
            res.push_back({c,1});
        }else{
            res.back().second++;
        }
    }
    return res;
}