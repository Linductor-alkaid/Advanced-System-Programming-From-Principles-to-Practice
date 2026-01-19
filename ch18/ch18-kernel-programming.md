# 第18章 Linux内核编程入门

> [返回目录](../README.md)

## 本章概述

内核编程是系统编程的最高境界，本章介绍Linux内核模块开发的基础知识。

## 本章小节

- [18.1 内核概述：用户态与内核态](./ch18-01-user-kernel-mode.md)
- [18.2 内核模块开发基础](./ch18-02-kernel-module.md)
  - [18.2.1 模块结构：init/exit](./ch18-02-01-module-structure.md)
  - [18.2.2 模块参数与模块信息](./ch18-02-02-module-info.md)
  - [18.2.3 模块加载与卸载](./ch18-02-03-module-load-unload.md)
- [18.3 内核中的并发控制](./ch18-03-kernel-concurrency.md)
  - [18.3.1 自旋锁](./ch18-03-01-spinlock.md)
  - [18.3.2 互斥锁](./ch18-03-02-mutex.md)
  - [18.3.3 原子操作](./ch18-03-03-atomic.md)
  - [18.3.4 RCU与读写锁](./ch18-03-04-rcu-rwlock.md)
- [18.4 内核内存管理](./ch18-04-kernel-memory.md)
  - [18.4.1 kmalloc/kfree](./ch18-04-01-kmalloc.md)
  - [18.4.2 vmalloc/vfree](./ch18-04-02-vmalloc.md)
  - [18.4.3 Slab分配器](./ch18-04-03-slab.md)
- [18.5 内核中的延迟与定时器](./ch18-05-delay-timer.md)
- [18.6 /proc与sysfs接口](./ch18-06-proc-sysfs.md)
- [18.7 字符设备驱动程序入门](./ch18-07-char-device.md)

## 学习目标

- 理解用户态与内核态的区别
- 掌握内核模块的开发方法
- 了解内核中的并发控制机制
- 掌握内核内存管理API
- 能够编写简单的字符设备驱动

---

*编写中...*
