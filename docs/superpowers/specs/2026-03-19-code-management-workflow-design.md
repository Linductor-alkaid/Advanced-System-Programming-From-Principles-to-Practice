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
│   ├── 01_01_basic_encapsulation.cpp       # 1.1节示例
│   ├── 01_01_basic_encapsulation.expected  # 期望输出
│   ├── 01_02a_public_access.cpp            # 1.2节示例a
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

- 源文件：`{章号}_{小节号}_{描述}.cpp`，描述用小写蛇形命名
- 多个示例：追加字母后缀 `{章号}_{小节号}{a|b|c}_{描述}.cpp`
- 期望输出：同名 `.expected` 文件
- 不确定输出：`.expected.regex`（正则匹配）或 `.expected.sorted`（排序后比较）

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
# 自动发现并注册本章所有 .cpp 文件为独立可执行目标
file(GLOB SOURCES "*.cpp")
foreach(SOURCE ${SOURCES})
    get_filename_component(NAME ${SOURCE} NAME_WE)
    add_executable(${NAME} ${SOURCE})
endforeach()
```

## 验证脚本 verify.sh

功能：
1. 在 `code/build/` 目录构建所有示例
2. 遍历所有 `.expected` 文件，运行对应可执行文件
3. 对比实际输出与期望输出
4. 支持三种匹配模式：精确匹配（`.expected`）、正则匹配（`.expected.regex`）、排序比较（`.expected.sorted`）
5. 汇总报告：总数 / 通过 / 失败

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
3. 编译运行，记录实际输出为 `.expected` 文件
4. 修复编译/运行错误的代码
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

步骤3: 编写 .expected 文件
       - 运行代码记录输出
       - 多线程等不确定输出用 .expected.sorted

步骤4: 更新 CMakeLists.txt
       - 顶层 add_subdirectory(chXX)
       - 章节 CMakeLists.txt 自动发现无需修改

步骤5: 运行 verify.sh 验证
       - 编译通过 + 输出匹配

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
