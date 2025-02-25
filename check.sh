#!/bin/bash

# C++ のコードをコンパイル
g++ main.cpp -std=c++17 -I . -o a.out 2>&1
if [ $? -ne 0 ]; then
    echo "❌ コンパイルエラー"
    exit 1
fi

# test ディレクトリ内の *.in ファイルを処理
for infile in test/*.in; do
    # 対応する .out ファイルのパスを取得
    outfile="${infile%.in}.out"

    # 実際の出力を一時ファイルに保存
    temp_output=$(mktemp)

    # ./a.out を実行し、失敗したらエラーメッセージを表示
    if ! ./a.out < "$infile" > "$temp_output"; then
        echo "❌ $(basename "$infile") : 実行エラー"
        rm "$temp_output"
        continue
    fi

    # 出力を比較（末尾の空白削除 & 最終行に改行を追加）
    normalized_outfile=$(mktemp)
    normalized_temp_output=$(mktemp)

    # 各ファイルを正規化（末尾の空白削除 & 最終行に改行を追加）
    sed 's/[ \t]*$//' "$outfile" | awk '1; END {if (NR > 0) print ""}' > "$normalized_outfile"
    sed 's/[ \t]*$//' "$temp_output" | awk '1; END {if (NR > 0) print ""}' > "$normalized_temp_output"

    if diff -u "$normalized_outfile" "$normalized_temp_output" > /dev/null; then
        echo "✅ $(basename "$infile") : OK"
    else
        echo "❌ $(basename "$infile") : NG"
        echo "=== 実際の出力 ==="
        cat "$temp_output"
        echo "=== 期待される出力 ==="
        cat "$outfile"
    fi

    # 一時ファイルを削除
    rm "$temp_output" "$normalized_outfile" "$normalized_temp_output"
done
