# 競技プログラミング精進（ユーザー：[melo25](https://atcoder.jp/users/melo25)）
## acc 使い方
```
acc new abc212

g++ main.cpp -std=c++17 -I .
oj t -c "./a.out" -d ./test/  
```
## 参考url
https://kankisenkowasuo.hatenablog.com/entry/2024/09/25/001415

## いつもの
```
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
```

## debug方法
problem.inが入力になるため、事前に入力を決めておく
1. ctrl + Shift + Bでビルドする
2. F5でデバッグを開始すればできる