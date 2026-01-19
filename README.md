# 高级系统编程：从原理到实践

> 面向大学应届毕业生的系统编程深度教程

---

## 目录导航

### 第一部分：C++核心特性深度剖析

- [第1章 封装 —— 数据保护的边界](ch01/ch01-encapsulation.md)
  - [1.1 封装的目标：数据隐藏与接口暴露](ch01/ch01-01-encapsulation-goal.md)
  - [1.2 访问修饰符的底层实现](ch01/ch01-02-access-modifiers.md)
  - [1.3 构造函数与析构函数的调用时机](ch01/ch01-03-ctor-dtor.md)
  - [1.4 RAII：资源管理即生命周期](ch01/ch01-04-raii.md)
  - [1.5 智能指针的现代封装实践](ch01/ch01-05-smart-ptr.md)

- [第2章 继承 —— 代码复用与层次设计](ch02/ch02-inheritance.md)
  - [2.1 继承的目标：代码复用与多态基础](ch02/ch02-01-inheritance-goal.md)
  - [2.2 单继承与多继承的内存布局](ch02/ch02-02-memory-layout.md)
  - [2.3 虚继承与菱形继承问题](ch02/ch02-03-virtual-inheritance.md)
  - [2.4 继承 vs 组合：设计决策](ch02/ch02-04-composition.md)
  - [2.5 CRTP：奇异递归模板模式](ch02/ch02-05-crtp.md)

- [第3章 多态 —— 动态分发的艺术](ch03/ch03-polymorphism.md)
  - [3.1 多态的目标：统一接口，不同实现](ch03/ch03-01-polymorphism-goal.md)
  - [3.2 静态多态：函数重载与模板](ch03/ch03-02-static-polymorphism.md)
  - [3.3 动态多态：虚函数与虚表](ch03/ch03-03-dynamic-polymorphism.md)
  - [3.4 虚函数表的内存布局与调用过程](ch03/ch03-04-vtable-layout.md)
  - [3.5 虚析构函数的重要性](ch03/ch03-05-virtual-dtor.md)
  - [3.6 final与override关键字](ch03/ch03-06-final-override.md)

---

### 第二部分：多线程编程

- [第4章 线程基础与原子操作](ch04/ch04-thread-atomic.md)
  - [4.1 进程 vs 线程：资源与调度的差异](ch04/ch04-01-process-thread.md)
  - [4.2 线程的创建与生命周期](ch04/ch04-02-thread-lifecycle.md)
  - [4.3 线程标识与线程间通信](ch04/ch04-03-thread-communication.md)
  - [4.4 原子操作详解](ch04/ch04-04-atomic-operations.md)
    - [4.4.1 原子类型与std::atomic](ch04/ch04-04-01-atomic-type.md)
    - [4.4.2 内存序：memory_order](ch04/ch04-04-02-memory-order.md)
    - [4.4.3 原子操作的实现原理（CAS指令）](ch04/ch04-04-03-cas-principle.md)
    - [4.4.4 ABA问题及其解决方案](ch04/ch04-04-04-aba-problem.md)
  - [4.5 CAS操作与无锁编程入门](ch04/ch04-05-lockfree-intro.md)

- [第5章 同步原语](ch05/ch05-synchronization.md)
  - [5.1 互斥锁：独占访问的实现原理](ch05/ch05-01-mutex.md)
  - [5.2 读写锁：读者-写者问题的解决方案](ch05/ch05-02-rwlock.md)
  - [5.3 条件变量：线程间的等待与通知机制](ch05/ch05-03-condition-variable.md)
  - [5.4 信号量：资源计数器](ch05/ch05-04-semaphore.md)
  - [5.5 屏障：集合点同步](ch05/ch05-05-barrier.md)

- [第6章 线程安全设计模式](ch06/ch06-thread-safe-patterns.md)
  - [6.1 守卫锁：RAII风格的锁管理](ch06/ch06-01-guard-lock.md)
  - [6.2 双重检查锁定：单例模式的线程安全实现](ch06/ch06-02-dclp.md)
  - [6.3 读写锁模式：Copy-on-Write](ch06/ch06-03-cow.md)
  - [6.4 生产者-消费者模式](ch06/ch06-04-producer-consumer.md)
  - [6.5 线程池设计：任务调度与资源复用](ch06/ch06-05-thread-pool.md)

- [第7章 无锁数据结构与算法](ch07/ch07-lockfree.md)
  - [7.1 无锁编程概述：优势与挑战](ch07/ch07-01-lockfree-overview.md)
  - [7.2 无锁栈：基于CAS的实现](ch07/ch07-02-lockfree-stack.md)
  - [7.3 无锁队列：Michael & Scott算法](ch07/ch07-03-lockfree-queue.md)
  - [7.4 无锁单向链表](ch07/ch07-04-lockfree-list.md)
  - [7.5 RCU（Read-Copy-Update）：读者无锁机制](ch07/ch07-05-rcu.md)
  - [7.6 无锁哈希表设计](ch07/ch07-06-lockfree-hashmap.md)
  - [7.7 无锁编程的陷阱与最佳实践](ch07/ch07-07-best-practices.md)

- [第8章 常见并发问题与调试](ch08/ch08-concurrency-issues.md)
  - [8.1 竞态条件：TOCTOU与数据竞争](ch08/ch08-01-race-condition.md)
  - [8.2 死锁：四个必要条件与预防策略](ch08/ch08-02-deadlock.md)
  - [8.3 活锁与饥饿](ch08/ch08-03-livelivelock-starvation.md)
  - [8.4 伪共享：缓存一致性问题的本质](ch08/ch08-04-false-sharing.md)
  - [8.5 并发调试工具与技巧](ch08/ch08-05-debugging-tools.md)

---

### 第三部分：内存管理

- [第9章 内存管理深度剖析](ch09/ch09-memory-management.md)
  - [9.1 内存区域划分：栈、堆、全局区、代码区](ch09/ch09-01-memory-regions.md)
  - [9.2 内存分配器的实现原理](ch09/ch09-02-allocator.md)
    - [9.2.1 dlmalloc与ptmalloc](ch09/ch09-02-01-ptmalloc.md)
    - [9.2.2 tcmalloc：Google的内存分配器](ch09/ch09-02-02-tcmalloc.md)
    - [9.2.3 jemalloc：Facebook的内存分配器](ch09/ch09-02-03-jemalloc.md)
  - [9.3 内存池设计：预分配与对象复用](ch09/ch09-03-memory-pool.md)
  - [9.4 对象池：减少分配/释放开销](ch09/ch09-04-object-pool.md)
  - [9.5 内存碎片：内部碎片与外部碎片](ch09/ch09-05-fragmentation.md)
  - [9.6 内存泄漏检测与预防](ch09/ch09-06-memory-leak.md)
  - [9.7 自定义内存管理与placement new](ch09/ch09-07-custom-allocator.md)

---

### 第四部分：系统实时性开发

- [第10章 时间与定时器](ch10/ch10-timer.md)
  - [10.1 时间源：CLOCK_REALTIME vs CLOCK_MONOTONIC vs CLOCK_BOOTTIME](ch10/ch10-01-clock-source.md)
  - [10.2 高精度定时器实现](ch10/ch10-02-high-precision-timer.md)
  - [10.3 定时器轮：时间轮算法](ch10/ch10-03-timing-wheel.md)
  - [10.4 最小堆定时器](ch10/ch10-04-heap-timer.md)
  - [10.5 时间轮与最小堆的性能对比](ch10/ch10-05-comparison.md)

- [第11章 I/O模型与事件驱动](ch11/ch11-io-models.md)
  - [11.1 I/O模型对比：阻塞/非阻塞/多路复用/信号驱动/异步](ch11/ch11-01-io-models-comparison.md)
  - [11.2 select/poll/epoll：原理与差异](ch11/ch11-02-select-poll-epoll.md)
  - [11.3 Reactor模式：事件分发与处理](ch11/ch11-03-reactor.md)
  - [11.4 Proactor模式：异步I/O](ch11/ch11-04-proactor.md)
  - [11.5 边缘触发 vs 电平触发](ch11/ch11-05-et-lt.md)
  - [11.6 事件驱动框架：libevent、libuv](ch11/ch11-06-event-frameworks.md)

- [第12章 实时调度策略](ch12/ch12-realtime-scheduling.md)
  - [12.1 调度策略：SCHED_OTHER/SCHED_FIFO/SCHED_RR/SCHED_DEADLINE](ch12/ch12-01-scheduling-policies.md)
  - [12.2 优先级反转与优先级继承](ch12/ch12-02-priority-inversion.md)
  - [12.3 CPU亲和性：绑定核心](ch12/ch12-03-cpu-affinity.md)
  - [12.4 实时编程的约束与限制](ch12/ch12-04-realtime-constraints.md)

- [第13章 性能优化技术](ch13/ch13-performance-optimization.md)
  - [13.1 缓存友好代码设计](ch13/ch13-01-cache-friendly.md)
  - [13.2 分支预测与代码优化](ch13/ch13-02-branch-prediction.md)
  - [13.3 SIMD指令入门](ch13/ch13-03-simd.md)
  - [13.4 性能分析工具：perf、gprof、valgrind](ch13/ch13-04-profiling-tools.md)
  - [13.5 热点优化实战案例](ch13/ch13-05-optimization-cases.md)

---

### 第五部分：网络编程

- [第14章 网络编程基础](ch14/ch14-network-basics.md)
  - [14.1 TCP/IP协议栈回顾](ch14/ch14-01-tcpip-stack.md)
  - [14.2 Socket API详解](ch14/ch14-02-socket-api.md)
    - [14.2.1 Socket创建与配置](ch14/ch14-02-01-socket-create.md)
    - [14.2.2 bind/listen/accept](ch14/ch14-02-02-bind-listen-accept.md)
    - [14.2.3 connect/send/recv](ch14/ch14-02-03-connect-send-recv.md)
  - [14.3 TCP协议细节：三次握手、四次挥手、拥塞控制](ch14/ch14-03-tcp-details.md)
  - [14.4 UDP协议与组播](ch14/ch14-04-udp-multicast.md)
  - [14.5 Socket选项与优化](ch14/ch14-05-socket-options.md)

- [第15章 高性能网络服务器模型](ch15/ch15-high-performance-server.md)
  - [15.1 传统并发模型：每连接一个进程/线程](ch15/ch15-01-traditional-model.md)
  - [15.2 Reactor模式：单线程/多线程Reactor](ch15/ch15-02-reactor-patterns.md)
  - [15.3 Proactor模式：基于异步I/O](ch15/ch15-03-proactor-pattern.md)
  - [15.4 主从Reactor：Netty/Muduo模式](ch15/ch15-04-master-slave-reactor.md)
  - [15.5 零拷贝技术：sendfile、splice、mmap](ch15/ch15-05-zero-copy.md)
  - [15.6 高性能框架案例：Muduo、ACE、Boost.Asio](ch15/ch15-06-frameworks.md)

- [第16章 RPC框架原理](ch16/ch16-rpc.md)
  - [16.1 RPC概述：从本地调用到远程调用](ch16/ch16-01-rpc-overview.md)
  - [16.2 序列化与反序列化](ch16/ch16-02-serialization.md)
  - [16.3 网络传输层设计](ch16/ch16-03-transport.md)
  - [16.4 服务注册与发现](ch16/ch16-04-service-discovery.md)
  - [16.5 负载均衡策略](ch16/ch16-05-load-balancing.md)
  - [16.6 开源RPC框架：gRPC、Thrift、brpc](ch16/ch16-06-frameworks.md)

---

### 第六部分：数据分发服务

- [第17章 数据分发服务DDS](ch17/ch17-dds.md)
  - [17.1 DDS概述：实时发布订阅协议](ch17/ch17-01-dds-overview.md)
  - [17.2 DDS核心概念](ch17/ch17-02-dds-concepts.md)
    - [17.2.1 Domain（域）](ch17/ch17-02-01-domain.md)
    - [17.2.2 Topic（主题）](ch17/ch17-02-02-topic.md)
    - [17.2.3 Publisher/Subscriber（发布者/订阅者）](ch17/ch17-02-03-pub-sub.md)
    - [17.2.4 DataWriter/DataReader（数据写入者/读取者）](ch17/ch17-02-04-datawriter-reader.md)
  - [17.3 QoS策略：质量服务策略详解](ch17/ch17-03-qos.md)
    - [17.3.1 可靠性QoS](ch17/ch17-03-01-reliability.md)
    - [17.3.2 持久性QoS](ch17/ch17-03-02-durability.md)
    - [17.3.3 延迟与吞吐量QoS](ch17/ch17-03-03-latency-throughput.md)
    - [17.3.4 资源限制QoS](ch17/ch17-03-04-resource-limits.md)
  - [17.4 DDS发现机制](ch17/ch17-04-discovery.md)
  - [17.5 DDS通信模型](ch17/ch17-05-communication.md)
  - [17.6 开源DDS实现：FastDDS、OpenDDS、CycloneDDS](ch17/ch17-06-implementations.md)

---

### 第七部分：内核编程基础

- [第18章 Linux内核编程入门](ch18/ch18-kernel-programming.md)
  - [18.1 内核概述：用户态与内核态](ch18/ch18-01-user-kernel-mode.md)
  - [18.2 内核模块开发基础](ch18/ch18-02-kernel-module.md)
    - [18.2.1 模块结构：init/exit](ch18/ch18-02-01-module-structure.md)
    - [18.2.2 模块参数与模块信息](ch18/ch18-02-02-module-info.md)
    - [18.2.3 模块加载与卸载](ch18/ch18-02-03-module-load-unload.md)
  - [18.3 内核中的并发控制](ch18/ch18-03-kernel-concurrency.md)
    - [18.3.1 自旋锁](ch18/ch18-03-01-spinlock.md)
    - [18.3.2 互斥锁](ch18/ch18-03-02-mutex.md)
    - [18.3.3 原子操作](ch18/ch18-03-03-atomic.md)
    - [18.3.4 RCU与读写锁](ch18/ch18-03-04-rcu-rwlock.md)
  - [18.4 内核内存管理](ch18/ch18-04-kernel-memory.md)
    - [18.4.1 kmalloc/kfree](ch18/ch18-04-01-kmalloc.md)
    - [18.4.2 vmalloc/vfree](ch18/ch18-04-02-vmalloc.md)
    - [18.4.3 Slab分配器](ch18/ch18-04-03-slab.md)
  - [18.5 内核中的延迟与定时器](ch18/ch18-05-delay-timer.md)
  - [18.6 /proc与sysfs接口](ch18/ch18-06-proc-sysfs.md)
  - [18.7 字符设备驱动程序入门](ch18/ch18-07-char-device.md)

- [第19章 内核调试与性能分析](ch19/ch19-kernel-debugging.md)
  - [19.1 内核调试技术](ch19/ch19-01-debug-techniques.md)
    - [19.1.1 printk与日志级别](ch19/ch19-01-01-printk.md)
    - [19.1.2 /proc/kallsyms与动态调试](ch19/ch19-01-02-kallsyms.md)
    - [19.1.3 crash工具分析内核崩溃](ch19/ch19-01-03-crash.md)
  - [19.2 内核追踪](ch19/ch19-02-tracing.md)
    - [19.2.1 ftrace追踪框架](ch19/ch19-02-01-ftrace.md)
    - [19.2.2 perf事件工具](ch19/ch19-02-02-perf.md)
    - [19.2.3 eBPF与BCC工具](ch19/ch19-02-03-ebpf.md)
  - [19.3 内核性能优化要点](ch19/ch19-03-optimization.md)

---

## 附录

- [附录A：开发环境搭建](appendix/appendix-a-environment.md)
- [附录B：常用工具参考](appendix/appendix-b-tools.md)
- [附录C：术语索引](appendix/appendix-c-glossary.md)
- [附录D：参考文献与资源](appendix/appendix-d-references.md)

---

## 文档说明

### 配套环境
- 操作系统：Linux（推荐Ubuntu 20.04+）
- 编译器：GCC 9.0+ 或 Clang 10.0+
- C++标准：C++11/14/17/20
- 调试工具：gdb、valgrind、perf

### 学习路径建议

```
路径1（应用开发）：
第1-3章 → 第4-6章 → 第9-10章 → 第14-15章

路径2（系统编程）：
第1-3章 → 第4-8章 → 第9-13章 → 第18-19章

路径3（全栈深入）：
全书按顺序学习
```

### 版本信息
- 当前版本：v2.0
- 创建日期：2026-01-19
- 最后更新：2026-01-19

---

*本文档采用 Markdown 格式编写，所有代码示例均可直接编译运行*
