# 代码管理与验证工作流设计

## 概述

为《系统高级编程：从原理到实践》建立统一的代码示例管理和验证机制。将嵌入在 Markdown 中的代码示例提取到独立的 `.cpp` 文件，通过 CMake 构建并自动验证输出正确性。同时定义后续章节编写的标准化工作流。

## 目标

1. 将 ch01-03 中的代码示例提取到 `code/` 目录，编译验证
2. 建立代码目录结构、命名规范和构建系统
3. 实现一键验证脚本（编译 + 运行 + 输出对比）
4. 定义后续章节编写的标准化流程

## 代码目录结构

```
code/
├── CMakeLists.txt                          # 顶层CMake：C++17标准、编译选项、子目录注册
├── verify.sh                               # 一键验证脚本
├── ch01/
│   ├── CMakeLists.txt                      # 本章编译目标注册
│   ├── 01_01_basic_encapsulation.cpp       # 1.1节示例（单个示例）
│   ├── 01_01_basic_encapsulation.expected  # 期望输出
│   ├── 01_02a_public_access.cpp            # 1.2节示例a（多个示例时用字母后缀）
│   ├── 01_02a_public_access.expected
│   ├── 01_02b_private_access.cpp           # 1.2节示例b
│   ├── 01_02b_private_access.expected
│   └── ...
├── ch02/
│   ├── CMakeLists.txt
│   └── ...
└── ch03/
    ├── CMakeLists.txt
    └── ...
```

### 命名规范

- **单个示例**：`{章号}_{小节号}_{描述}.cpp`，描述用小写蛇形命名
- **多个示例**：`{章号}_{小节号}{a|b|c}_{描述}.cpp`（字母紧跟小节号）
- **规则**：当一个小节有多个示例时，全部使用字母后缀，不存在无字母的同名文件
- 期望输出：同名 `.expected` 文件

### 验证模式

根据代码特性选择对应的验证模式：

| 模式 | 标记文件 | 适用场景 | 行为 |
|------|----------|----------|------|
| **精确匹配** | `.expected` | 输出确定的普通示例 | `diff` 对比 stdout |
| **正则匹配** | `.expected.regex` | 输出含地址、时间戳等运行时变化值 | 逐行正则匹配 |
| **排序比较** | `.expected.sorted` | 输出行顺序不确定但内容确定 | 排序后 `diff` |
| **仅退出码** | `.exitonly` | 多线程、输出完全不确定的示例 | 仅检查退出码为0 |
| **仅编译** | `.buildonly` | 需要特权/特殊环境的示例（如实时调度、内核模块） | 仅编译不运行 |

**选择指南**：
- ch01-03 中打印地址/指针值的示例 → `.expected.regex`
- ch04-08 多线程示例输出顺序不确定 → `.exitonly`
- ch12 实时调度（需要 root 权限）→ `.buildonly`
- 其他常规示例 → `.expected`

## 构建系统

### 顶层 CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.16)
project(AdvancedSystemProgrammingExamples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

add_subdirectory(ch01)
add_subdirectory(ch02)
add_subdirectory(ch03)
```

### 章节 CMakeLists.txt（以 ch01 为例）

```cmake
# 获取章节目录名作为目标名前缀，避免跨章节目标名冲突
get_filename_component(CHAPTER_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# 自动发现并注册本章所有 .cpp 文件为独立可执行目标
file(GLOB SOURCES "*.cpp")
foreach(SOURCE ${SOURCES})
    get_filename_component(STEM ${SOURCE} NAME_WE)
    set(TARGET_NAME ${CHAPTER_DIR}_${STEM})
    add_executable(${TARGET_NAME} ${SOURCE})
    # 将可执行文件输出到 build/{章节目录}/ 下，方便 verify.sh 查找
    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CHAPTER_DIR})
endforeach()
```

**目标命名**：`ch01_01_01_basic_encapsulation`（章节前缀 + 文件名），确保全局唯一。

**可执行文件位置**：`build/ch01/ch01_01_01_basic_encapsulation`，与源文件一一对应。

## 验证脚本 verify.sh

### 二进制路径映射

源文件 `code/ch01/01_01_basic_encapsulation.cpp` 对应：
- CMake 目标名：`ch01_01_01_basic_encapsulation`
- 可执行文件路径：`build/ch01/ch01_01_01_basic_encapsulation`

### 工作流程

```bash
#!/bin/bash
# verify.sh - 编译并验证所有代码示例

BUILD_DIR="build"
FILTER="${1:-}"  # 可选：章节过滤，如 "ch01"

# 1. 构建
cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE=Debug
cmake --build "$BUILD_DIR" -j$(nproc)

# 2. 遍历章节目录
TOTAL=0; PASS=0; FAIL=0; SKIP=0

for CHAPTER_DIR in ch*/; do
    [[ -n "$FILTER" && "$CHAPTER_DIR" != "${FILTER}/" ]] && continue
    CHAPTER=$(basename "$CHAPTER_DIR")

    for CPP in "$CHAPTER_DIR"*.cpp; do
        STEM=$(basename "$CPP" .cpp)
        BINARY="$BUILD_DIR/$CHAPTER/${CHAPTER}_${STEM}"
        ((TOTAL++))

        # 确定验证模式
        if [[ -f "$CHAPTER_DIR${STEM}.buildonly" ]]; then
            # 仅编译模式：编译成功即通过
            echo "BUILD  $CHAPTER/$STEM"
            ((PASS++)); ((SKIP++))
            continue
        fi

        if [[ -f "$CHAPTER_DIR${STEM}.exitonly" ]]; then
            # 仅退出码模式：运行并检查退出码
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
        ACTUAL=$("$BINARY" 2>/dev/null)

        if [[ -f "$CHAPTER_DIR${STEM}.expected" ]]; then
            EXPECTED=$(cat "$CHAPTER_DIR${STEM}.expected")
            if [[ "$ACTUAL" == "$EXPECTED" ]]; then
                echo "PASS   $CHAPTER/$STEM"
                ((PASS++))
            else
                echo "FAIL   $CHAPTER/$STEM"
                diff <(echo "$ACTUAL") <(echo "$EXPECTED")
                ((FAIL++))
            fi
        elif [[ -f "$CHAPTER_DIR${STEM}.expected.sorted" ]]; then
            EXPECTED=$(sort "$CHAPTER_DIR${STEM}.expected.sorted")
            ACTUAL_SORTED=$(echo "$ACTUAL" | sort)
            if [[ "$ACTUAL_SORTED" == "$EXPECTED" ]]; then
                echo "PASS   $CHAPTER/$STEM (sorted)"
                ((PASS++))
            else
                echo "FAIL   $CHAPTER/$STEM (sorted)"
                ((FAIL++))
            fi
        elif [[ -f "$CHAPTER_DIR${STEM}.expected.regex" ]]; then
            # 逐行正则匹配
            MATCH=true
            while IFS= read -r pattern && IFS= read -r line <&3; do
                if ! [[ "$line" =~ $pattern ]]; then
                    MATCH=false; break
                fi
            done < "$CHAPTER_DIR${STEM}.expected.regex" 3<<< "$ACTUAL"
            if $MATCH; then
                echo "PASS   $CHAPTER/$STEM (regex)"
                ((PASS++))
            else
                echo "FAIL   $CHAPTER/$STEM (regex)"
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
[[ $FAIL -eq 0 ]] && exit 0 || exit 1
```

用法：
```bash
cd code
./verify.sh          # 验证所有章节
./verify.sh ch01     # 只验证第1章
```

## Markdown 引用规范

在文章中每个代码示例块后添加源文件引用链接：

```markdown
> 📁 完整代码：[code/ch01/01_01_basic_encapsulation.cpp](../code/ch01/01_01_basic_encapsulation.cpp)
```

## 对已有章节（ch01-03）的处理

1. 逐章阅读 Markdown，识别所有独立的代码示例
2. 为每个示例创建独立 `.cpp` 文件（补充必要的 `#include` 和 `main` 函数）
3. 编译运行，检查编译错误并修复
4. 根据输出特性选择验证模式：
   - 输出含地址/指针值 → 编写 `.expected.regex`（用正则通配地址部分）
   - 输出确定 → 记录实际输出为 `.expected`
5. 在 Markdown 原文中添加源文件引用链接
6. 运行 `verify.sh` 确认全部通过

## 后续章节编写工作流

每个新章节遵循以下流程：

```
步骤1: 编写 Markdown 内容
       - 按企划模板：实现目标→核心原理→架构图→代码示例→深入讲解

步骤2: 提取代码到 code/chXX/
       - 创建独立 .cpp 文件
       - 补充完整的 #include 和 main 函数

步骤3: 选择验证模式并创建标记文件
       - 确定输出 → .expected（记录运行输出）
       - 含地址/时间戳 → .expected.regex（正则通配）
       - 行序不确定 → .expected.sorted
       - 多线程/完全不确定 → .exitonly
       - 需特权/特殊环境 → .buildonly

步骤4: 更新 CMakeLists.txt
       - 顶层 add_subdirectory(chXX)
       - 章节 CMakeLists.txt 模板复制即可，自动发现无需修改

步骤5: 运行 verify.sh 验证
       - 编译通过 + 验证通过

步骤6: 添加 Markdown 引用链接
       - 每个代码块后添加源文件路径

步骤7: 最终验证
       - 全量运行 verify.sh 确保无回归
```

## 技术约束

- C++ 标准：C++17
- 编译器：GCC 9.0+ 或 Clang 10.0+
- 操作系统：Linux（Ubuntu 20.04+）
- 编译选项：`-Wall -Wextra -g`
- 每个 `.cpp` 文件必须是独立可编译的（自包含所有依赖）
- 多线程示例建议添加 `-fsanitize=thread` 编译选项（可选，通过 CMake option 控制）
