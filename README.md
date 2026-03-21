# 競技プログラミング精進（ユーザー：[melo25](https://atcoder.jp/users/melo25)）
# 目標
- abc212からabc318までを完全に解けるようにする
- 1週目：緑diffまで
- 2周目：水diffまで
- 3周目：青diffまで

# やり方
- 各問題について解法を考えて思いついたら解説を見る。AIなどを使って賢い書き方を見る
- そのやり方に従って提出して解けることを確認する
- それが出来たら最初からやり直して短時間で何も見ずに解けるようになる

## acc 使い方
```
acc new abc212

g++ main.cpp -std=c++17 -I .
oj t -c "./a.out" -d ./tests/  
```
## 参考url
https://kankisenkowasuo.hatenablog.com/entry/2024/09/25/001415
https://zenn.dev/fro25zen/articles/atcoder_setup_article

## acc loginができなくなったら
https://kaiyou9.com/acc_and_oj_login_failed/

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