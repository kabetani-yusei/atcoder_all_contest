#!/usr/bin/env python3

from collections import Counter
from pathlib import Path
import sys


GREEN = "\033[32m"
RED = "\033[31m"
RESET = "\033[0m"
BASE_DIR = Path(__file__).resolve().parent


def read_cases(path: Path) -> list[str]:
    tokens = path.read_text().split()
    cases: list[str] = []
    index = 0

    while index < len(tokens):
        n = int(tokens[index])
        index += 1
        if n == 0:
            break
        if index >= len(tokens):
            raise ValueError("in.txt: 文字列が足りません")

        s = tokens[index]
        index += 1
        if len(s) != n:
            raise ValueError(
                f"in.txt: N={n} に対して文字列長が {len(s)} です"
            )
        cases.append(s)

    return cases


def main() -> int:
    try:
        cases = read_cases(BASE_DIR / "in.txt")
        expected = (BASE_DIR / "ans.txt").read_text().splitlines()
        actual = (BASE_DIR / "out.txt").read_text().splitlines()
    except (OSError, ValueError) as error:
        print(f"{RED}チェックできません: {error}{RESET}")
        return 1

    errors: list[str] = []

    if len(expected) != len(cases):
        errors.append(
            f"ans.txt の行数が不正です "
            f"(テストケース: {len(cases)}, ans.txt: {len(expected)})"
        )

    if len(actual) != len(cases):
        errors.append(
            f"out.txt の行数が不正です "
            f"(期待: {len(cases)}, 実際: {len(actual)})"
        )

    check_count = min(len(cases), len(expected), len(actual))
    for case_number in range(1, check_count + 1):
        original = cases[case_number - 1]
        answer = expected[case_number - 1]
        output = actual[case_number - 1]

        if answer == "IMPOSSIBLE":
            if output != "IMPOSSIBLE":
                errors.append(
                    f"case {case_number}: IMPOSSIBLE を出力すべきです "
                    f"(out: {output!r})"
                )
            continue

        if output == "IMPOSSIBLE":
            errors.append(
                f"case {case_number}: 並べ替え可能ですが IMPOSSIBLE が出力されています"
            )
        elif len(output) != len(original):
            errors.append(
                f"case {case_number}: 文字列長が違います "
                f"(期待: {len(original)}, 実際: {len(output)})"
            )
        elif Counter(output) != Counter(original):
            errors.append(
                f"case {case_number}: S の文字を並べ替えた文字列ではありません "
                f"(S: {original!r}, out: {output!r})"
            )
        elif output == original:
            errors.append(
                f"case {case_number}: 元の文字列 S と同じです (S: {original!r})"
            )

    if errors:
        print(f"{RED}不正解です{RESET}")
        for error in errors:
            print(f"{RED}- {error}{RESET}")
        return 1

    print(f"{GREEN}正解です（{len(cases)} ケース）{RESET}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
