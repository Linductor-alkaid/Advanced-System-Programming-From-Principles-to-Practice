#!/bin/bash
# verify.sh - 编译并验证所有代码示例
set -uo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

BUILD_DIR="build"
FILTER="${1:-}"

# 1. 构建
echo "=== Building ==="
cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug 2>&1
cmake --build "$BUILD_DIR" -j"$(nproc)" 2>&1

BUILD_RET=$?
if [ $BUILD_RET -ne 0 ]; then
    echo "BUILD FAILED"
    exit 1
fi

echo ""
echo "=== Verifying ==="

TOTAL=0; PASS=0; FAIL=0; SKIP=0

for CHAPTER_DIR in ch*/; do
    [ -d "$CHAPTER_DIR" ] || continue
    [[ -n "$FILTER" && "$CHAPTER_DIR" != "${FILTER}/" ]] && continue
    CHAPTER=$(basename "$CHAPTER_DIR")

    for CPP in "$CHAPTER_DIR"*.cpp; do
        [ -f "$CPP" ] || continue
        STEM=$(basename "$CPP" .cpp)
        BINARY="$BUILD_DIR/$CHAPTER/${CHAPTER}_${STEM}"
        ((TOTAL++))

        if [ ! -f "$BINARY" ]; then
            echo "MISS   $CHAPTER/$STEM (binary not found)"
            ((FAIL++))
            continue
        fi

        # 仅编译模式
        if [ -f "$CHAPTER_DIR${STEM}.buildonly" ]; then
            echo "BUILD  $CHAPTER/$STEM"
            ((PASS++))
            continue
        fi

        # 仅退出码模式
        if [ -f "$CHAPTER_DIR${STEM}.exitonly" ]; then
            if "$BINARY" > /dev/null 2>&1; then
                echo "PASS   $CHAPTER/$STEM (exit-only)"
                ((PASS++))
            else
                echo "FAIL   $CHAPTER/$STEM (non-zero exit)"
                ((FAIL++))
            fi
            continue
        fi

        # 运行并捕获输出
        ACTUAL=$("$BINARY" 2>/dev/null) || true

        # 精确匹配
        if [ -f "$CHAPTER_DIR${STEM}.expected" ]; then
            EXPECTED=$(cat "$CHAPTER_DIR${STEM}.expected")
            if [ "$ACTUAL" = "$EXPECTED" ]; then
                echo "PASS   $CHAPTER/$STEM"
                ((PASS++))
            else
                echo "FAIL   $CHAPTER/$STEM"
                diff <(echo "$ACTUAL") "$CHAPTER_DIR${STEM}.expected" || true
                ((FAIL++))
            fi
        # 排序比较
        elif [ -f "$CHAPTER_DIR${STEM}.expected.sorted" ]; then
            EXPECTED_SORTED=$(sort "$CHAPTER_DIR${STEM}.expected.sorted")
            ACTUAL_SORTED=$(echo "$ACTUAL" | sort)
            if [ "$ACTUAL_SORTED" = "$EXPECTED_SORTED" ]; then
                echo "PASS   $CHAPTER/$STEM (sorted)"
                ((PASS++))
            else
                echo "FAIL   $CHAPTER/$STEM (sorted)"
                diff <(echo "$ACTUAL_SORTED") <(echo "$EXPECTED_SORTED") || true
                ((FAIL++))
            fi
        # 正则匹配
        elif [ -f "$CHAPTER_DIR${STEM}.expected.regex" ]; then
            MATCH=true
            LINE_NUM=0
            while IFS= read -r pattern; do
                ((LINE_NUM++))
                LINE=$(echo "$ACTUAL" | sed -n "${LINE_NUM}p")
                if ! [[ "$LINE" =~ $pattern ]]; then
                    echo "FAIL   $CHAPTER/$STEM (regex line $LINE_NUM)"
                    echo "  pattern:  $pattern"
                    echo "  actual:   $LINE"
                    MATCH=false
                    break
                fi
            done < "$CHAPTER_DIR${STEM}.expected.regex"
            if $MATCH; then
                echo "PASS   $CHAPTER/$STEM (regex)"
                ((PASS++))
            else
                ((FAIL++))
            fi
        else
            echo "SKIP   $CHAPTER/$STEM (no expected file)"
            ((SKIP++))
        fi
    done
done

echo ""
echo "=== Results: $TOTAL total, $PASS passed, $FAIL failed, $SKIP skipped ==="
[ "$FAIL" -eq 0 ] && exit 0 || exit 1
