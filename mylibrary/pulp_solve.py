# main.py
# ============================================================
# AtCoder における PuLP の使い方まとめ
# ============================================================
#
# PuLP は線形計画問題 / 整数計画問題 / 0-1 整数計画問題を Python で書けるライブラリです。
#
# AtCoder では次のように import して使えます。
#
#     import pulp
#
# 典型的な流れ:
#
# 1. 問題を作る
#       prob = pulp.LpProblem("名前", pulp.LpMaximize)
#       prob = pulp.LpProblem("名前", pulp.LpMinimize)
#
# 2. 変数を作る
#       x = pulp.LpVariable("x", lowBound=0, cat="Integer")
#       y = pulp.LpVariable("y", lowBound=0, cat="Continuous")
#       z = pulp.LpVariable("z", cat="Binary")
#
#    cat の代表例:
#       "Continuous" : 実数変数
#       "Integer"    : 整数変数
#       "Binary"     : 0/1 変数
#
# 3. 目的関数を追加する
#       prob += 3 * x + 2 * y
#
# 4. 制約を追加する
#       prob += x + y <= 10
#       prob += 2 * x - y >= 3
#       prob += x == 5
#
# 5. 解く
#       status = prob.solve(pulp.PULP_CBC_CMD(msg=False))
#
# 6. 解を取り出す
#       ans = pulp.value(prob.objective)
#       xv = pulp.value(x)
#
#    整数変数の値は 3.0 のような float で返ることがあるので、
#    int(round(pulp.value(x))) とするのが安全です。
#
# 注意:
#   - PuLP は強力ですが、ソルバー起動が重いです。
#   - T が大きい問題、変数数・制約数が大きい問題では TLE しやすいです。
#   - AtCoder で使うなら「小さい ILP」「場合分け検証」「ヒューリスティック補助」向きです。
#   - 本当に提出するなら、可能なら数式を整理して O(1), O(log N), O(N) などに落とす方が安全です。
#
# ============================================================

import sys
import pulp


# ------------------------------------------------------------
# 例1: 最小限の整数計画問題
# ------------------------------------------------------------
#
# maximize x + y
# subject to
#   2x + y <= 8
#   x + 2y <= 8
#   x, y >= 0
#   x, y are integers
#
def sample_integer_programming():
    prob = pulp.LpProblem("sample_integer_programming", pulp.LpMaximize)

    x = pulp.LpVariable("x", lowBound=0, cat="Integer")
    y = pulp.LpVariable("y", lowBound=0, cat="Integer")

    # 目的関数
    prob += x + y

    # 制約
    prob += 2 * x + y <= 8
    prob += x + 2 * y <= 8

    status = prob.solve(pulp.PULP_CBC_CMD(msg=False))

    if pulp.LpStatus[status] != "Optimal":
        return None

    ans = int(round(pulp.value(prob.objective)))
    xv = int(round(pulp.value(x)))
    yv = int(round(pulp.value(y)))

    return ans, xv, yv


# ------------------------------------------------------------
# 例2: 0-1 ナップサックを PuLP で書く
# ------------------------------------------------------------
#
# N 個の品物があり、品物 i は価値 v[i], 重さ w[i]。
# 重さ合計を W 以下にして、価値合計を最大化する。
#
# x[i] = 1 なら品物 i を選ぶ、0 なら選ばない。
#
def knapsack_with_pulp(N, W, weights, values):
    prob = pulp.LpProblem("knapsack", pulp.LpMaximize)

    x = [
        pulp.LpVariable(f"x_{i}", cat="Binary")
        for i in range(N)
    ]

    # 目的関数: 価値合計を最大化
    prob += pulp.lpSum(values[i] * x[i] for i in range(N))

    # 制約: 重さ合計が W 以下
    prob += pulp.lpSum(weights[i] * x[i] for i in range(N)) <= W

    status = prob.solve(pulp.PULP_CBC_CMD(msg=False))

    if pulp.LpStatus[status] != "Optimal":
        return None

    best_value = int(round(pulp.value(prob.objective)))
    selected = [
        i for i in range(N)
        if int(round(pulp.value(x[i]))) == 1
    ]

    return best_value, selected


# ------------------------------------------------------------
# 例3: 変数を dict で持つ
# ------------------------------------------------------------
#
# 多次元添字の変数を作りたいときは dict が便利です。
#
def assignment_example(cost):
    # cost[i][j] = 人 i を仕事 j に割り当てるコスト
    N = len(cost)

    prob = pulp.LpProblem("assignment", pulp.LpMinimize)

    x = {}
    for i in range(N):
        for j in range(N):
            x[i, j] = pulp.LpVariable(f"x_{i}_{j}", cat="Binary")

    # コスト最小化
    prob += pulp.lpSum(cost[i][j] * x[i, j] for i in range(N) for j in range(N))

    # 各人はちょうど1つの仕事をする
    for i in range(N):
        prob += pulp.lpSum(x[i, j] for j in range(N)) == 1

    # 各仕事はちょうど1人に割り当てる
    for j in range(N):
        prob += pulp.lpSum(x[i, j] for i in range(N)) == 1

    status = prob.solve(pulp.PULP_CBC_CMD(msg=False))

    if pulp.LpStatus[status] != "Optimal":
        return None

    min_cost = int(round(pulp.value(prob.objective)))

    assign = [-1] * N
    for i in range(N):
        for j in range(N):
            if int(round(pulp.value(x[i, j]))) == 1:
                assign[i] = j

    return min_cost, assign


# ------------------------------------------------------------
# 例4: 現在話していたじゃんけん問題を PuLP で書く場合
# ------------------------------------------------------------
#
# 注意:
#   T <= 5 * 10^5 のように大きい問題では、これは提出向きではありません。
#   あくまで「定式化を PuLP で確認する」用です。
#
# 手の個数:
#   a = グー
#   b = チョキ
#   c = パー
#
# 勝者パターン:
#   x: g-p-g の p 勝者数
#   y: c-g-c の g 勝者数
#   z: p-c-p の c 勝者数
#
# 直線パーツとして考えると、
#   x > 0 なら g が x+1 個, p が x 個必要
#   y > 0 なら c が y+1 個, g が y 個必要
#   z > 0 なら p が z+1 個, c が z 個必要
#
# x > 0 かどうかを dx という 0/1 変数で表す。
#
def janken_with_pulp(a, b, c):
    M = a + b + c

    prob = pulp.LpProblem("janken", pulp.LpMaximize)

    x = pulp.LpVariable("x", lowBound=0, cat="Integer")
    y = pulp.LpVariable("y", lowBound=0, cat="Integer")
    z = pulp.LpVariable("z", lowBound=0, cat="Integer")

    dx = pulp.LpVariable("dx", cat="Binary")
    dy = pulp.LpVariable("dy", cat="Binary")
    dz = pulp.LpVariable("dz", cat="Binary")

    # 目的関数: 勝者数を最大化
    prob += x + y + z

    # 使う手の個数制約
    prob += x + dx + y <= a  # グー
    prob += y + dy + z <= b  # チョキ
    prob += z + dz + x <= c  # パー

    # dx = 1 <=> x >= 1 に近い関係を作る
    prob += x <= M * dx
    prob += y <= M * dy
    prob += z <= M * dz

    prob += x >= dx
    prob += y >= dy
    prob += z >= dz

    status = prob.solve(pulp.PULP_CBC_CMD(msg=False))

    if pulp.LpStatus[status] != "Optimal":
        return None

    ans = (
        int(round(pulp.value(x))) +
        int(round(pulp.value(y))) +
        int(round(pulp.value(z)))
    )

    # 円全体が2種類の完全交互になる場合だけ、
    # 「勝者 k 人に対して周囲の手が k+1 個必要」ではなく k 個で足りる。
    #
    # g-p-g-p-... の円なら p が全員勝者
    if b == 0 and a == c:
        ans = max(ans, a)

    # c-g-c-g-... の円なら g が全員勝者
    if c == 0 and a == b:
        ans = max(ans, a)

    # p-c-p-c-... の円なら c が全員勝者
    if a == 0 and b == c:
        ans = max(ans, b)

    return ans


# ------------------------------------------------------------
# AtCoder でよく使う読み取り main
# ------------------------------------------------------------
#
# この main は、例4のじゃんけん問題用です。
# 別の問題で使う場合は、solve_one_case の中身を書き換えてください。
#
def solve_one_case(a, b, c):
    return janken_with_pulp(a, b, c)


def main():
    input = sys.stdin.readline

    T = int(input())
    out = []

    for _ in range(T):
        a, b, c = map(int, input().split())
        ans = solve_one_case(a, b, c)
        out.append(str(ans))

    print("\n".join(out))


if __name__ == "__main__":
    main()
