# 附录B：常用工具参考

> [返回目录](../README.md)

## B.1 调试工具

| 工具 | 用途 | 常用命令 |
|------|------|----------|
| gdb | 源码级调试 | `break`, `run`, `step`, `print` |
| valgrind | 内存检测 | `valgrind --leak-check=full` |
| strace | 系统调用跟踪 | `strace -e trace=open,read` |

## B.2 性能分析工具

| 工具 | 用途 | 常用命令 |
|------|------|----------|
| perf | CPU性能分析 | `perf top`, `perf record` |
| gprof | 函数级性能分析 | 编译加`-pg`选项 |
| time | 程序运行时间 | `time ./program` |

## B.3 并发调试工具

| 工具 | 用途 |
|------|------|
| ThreadSanitizer | 数据竞争检测 |
| Helgrind | 锁错误检测 |

---

*编写中...*
