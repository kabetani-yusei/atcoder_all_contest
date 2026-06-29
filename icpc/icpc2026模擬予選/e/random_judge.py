#!/usr/bin/env python3
"""main.cpp をランダムな秘密値で検査するローカル対話ジャッジ。"""

from __future__ import annotations

import argparse
import atexit
import math
import os
import random
import select
import subprocess
import sys
from pathlib import Path


LIMIT = 10**18
QUERY_LIMIT = 100
ROOT = Path(__file__).resolve().parent


def read_line(proc: subprocess.Popen[str], timeout: float) -> str | None:
    ready, _, _ = select.select([proc.stdout], [], [], timeout)
    if not ready:
        return None
    return proc.stdout.readline()


def run_case(executable: Path, a: int, b: int, timeout: float) -> tuple[bool, str, list[str]]:
    proc = subprocess.Popen(
        [str(executable)],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        bufsize=1,
    )
    transcript: list[str] = []
    queries = 0
    verdict = "解答を出力せずに終了しました"

    try:
        while True:
            line = read_line(proc, timeout)
            if line is None:
                verdict = f"{timeout} 秒以内に出力されませんでした"
                break
            if line == "":
                verdict = "解答を出力せずに終了しました"
                break

            output = line.rstrip("\r\n")
            transcript.append(f"Write: {output}")
            tokens = output.split()

            if len(tokens) == 3 and tokens[0] == "?":
                queries += 1
                if queries > QUERY_LIMIT:
                    verdict = f"質問回数が {QUERY_LIMIT} 回を超えました"
                    break
                try:
                    x, y = map(int, tokens[1:])
                except ValueError:
                    verdict = f"質問の整数形式が不正です: {output}"
                    break
                if not (0 <= x <= LIMIT and 0 <= y <= LIMIT):
                    verdict = f"質問値が範囲外です: {output}"
                    break
                response = math.gcd(a + x, b + y)
                transcript.append(f"Read: {response}")
                assert proc.stdin is not None
                proc.stdin.write(f"{response}\n")
                proc.stdin.flush()
                continue

            if len(tokens) == 3 and tokens[0] == "!":
                try:
                    answer_a, answer_b = map(int, tokens[1:])
                except ValueError:
                    verdict = f"解答の整数形式が不正です: {output}"
                    break
                if (answer_a, answer_b) == (a, b):
                    return True, "AC", transcript
                verdict = f"誤答を出力しました: {answer_a} {answer_b}"
                break

            verdict = f"出力形式が不正です: {output}"
            break
    finally:
        if proc.poll() is None:
            proc.kill()
        proc.wait()

    assert proc.stderr is not None
    stderr = proc.stderr.read().strip()
    if stderr:
        transcript.append(f"stderr: {stderr}")
    return False, verdict, transcript


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--cases", type=int, default=100)
    parser.add_argument("--seed", type=int, default=None)
    parser.add_argument("--timeout", type=float, default=2.0)
    args = parser.parse_args()

    source = ROOT / "main.cpp"
    executable = Path("/tmp") / f"icpc_e_random_judge_{os.getpid()}"
    atexit.register(executable.unlink, missing_ok=True)
    compile_result = subprocess.run(
        ["g++", "-std=c++20", "-O2", "-Wall", "-Wextra", str(source), "-o", str(executable)],
        text=True,
        capture_output=True,
    )
    if compile_result.returncode != 0:
        print("コンパイルに失敗しました", file=sys.stderr)
        print(compile_result.stderr, file=sys.stderr)
        return 2

    used_seed = args.seed if args.seed is not None else random.SystemRandom().randrange(2**64)
    rng = random.Random(used_seed)
    for case_no in range(1, args.cases + 1):
        a = rng.randint(1, 10**9)
        b = rng.randint(1, 10**9)
        ok, verdict, transcript = run_case(executable, a, b, args.timeout)
        if not ok:
            print(f"WA: case {case_no}/{args.cases}")
            print(f"seed: {used_seed!r}")
            print(f"問題（秘密値）: a={a}, b={b}")
            print(f"正しい答え: ! {a} {b}")
            print(f"判定理由: {verdict}")
            print("対話履歴:")
            print("\n".join(transcript))
            return 1

    print(f"AC: ランダム {args.cases} ケースすべて正解しました (seed={used_seed!r})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
