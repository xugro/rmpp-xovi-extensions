#!/bin/bash
# This script is meant to be executed by the github action.

SCR_ROOT=$(pwd)
export TMP=$SCR_ROOT/tmp/xovi-extensions
export XOVI_REPO=/tmp/xovi
mkdir -p $TMP
mkdir -p "$XOVI_REPO/util"
curl -o "$XOVI_REPO/util/xovigen.py" https://raw.githubusercontent.com/asivery/xovi/1edb3c9f0a31daec31b6931eb00f4f6ecc56d72b/util/xovigen.py

for dir in ../*; do
    if [ -d $dir ] && [ $dir != "../scripts" ]; then
        echo "Building from $dir..."
        cd "$dir"
        bash make-aarch64.sh
        cd "$SCR_ROOT"
    fi
done


mkdir output
find .. -iname "*.so" -not -path "**/release/deps/**" -exec cp -v {} output \;

