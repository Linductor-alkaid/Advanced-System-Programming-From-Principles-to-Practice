# 第4章 线程基础与原子操作

> [返回目录](../README.md)

## 本章概述

线程是现代程序并发执行的基本单元。本章介绍线程的基础知识以及原子操作——无锁编程的基础。

## 本章小节

- [4.1 进程 vs 线程：资源与调度的差异](./ch04-01-process-thread.md)
- [4.2 线程的创建与生命周期](./ch04-02-thread-lifecycle.md)
- [4.3 线程标识与线程间通信](./ch04-03-thread-communication.md)
- [4.4 原子操作详解](./ch04-04-atomic-operations.md)
  - [4.4.1 原子类型与std::atomic](./ch04-04-01-atomic-type.md)
  - [4.4.2 内存序：memory_order](./ch04-04-02-memory-order.md)
  - [4.4.3 原子操作的实现原理（CAS指令）](./ch04-04-03-cas-principle.md)
  - [4.4.4 ABA问题及其解决方案](./ch04-04-04-aba-problem.md)
- [4.5 CAS操作与无锁编程入门](./ch04-05-lockfree-intro.md)

## 学习目标

- 理解进程与线程的区别
- 掌握线程的创建和管理
- 理解原子操作的概念和内存序
- 掌握CAS操作原理
- 了解ABA问题及解决方案

## 思考题

1. 进程和线程在资源隔离上有什么本质区别？
2. 为什么需要内存序？不同的memory_order有什么区别？
3. ABA问题是如何产生的？有哪些解决方案？

---

*编写中...*
