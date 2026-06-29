#!/usr/bin/env bash

set -euo pipefail

template="icpc/template.cpp"

if [[ ! -f "$template" ]]; then
    echo "Error: icpc/template.cpp was not found." >&2
    exit 1
fi

for problem in {a..h}; do
    directory="icpc_set/$problem"
    mkdir -p "$directory"
    touch "$directory/in.txt" "$directory/out.txt" "$directory/ans.txt"
    cp "$template" "$directory/main.cpp"
    cp "$(dirname "$0")/icpc/run.sh" "$directory/run.sh"
    chmod +x "$directory/run.sh"
done
