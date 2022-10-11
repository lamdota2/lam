**[TOC]**

- [调查hang和常见进程问题](#调查hang和常见进程问题)
- [gdb attach](#gdb-attach)
- [ftrace](#ftrace)
- [查看进程下的所有线程](#查看进程下的所有线程)
 
### 调查hang和常见进程问题

### gdb attach

```bash script
root@asp-1a:~ >cat /proc/9259/stack
[<0>] futex_wait_queue_me+0xb4/0x110
[<0>] futex_wait+0xe9/0x240
[<0>] do_futex+0x178/0xbc0
[<0>] __x64_sys_futex+0x146/0x1c0
[<0>] do_syscall_64+0x33/0x40
[<0>] entry_SYSCALL_64_after_hwframe+0x44/0xa9
   
```
### ftrace

### 查看进程下的所有线程
pstree -t

https://ecotrust-canada.github.io/markdown-toc/



### 生成标题
其实只要把"[TOC]"换成下方所示语法即可

- [显示在目录上的一级标题名](#实际一级标题名)
  - [显示在目录上的二级标题名](#实际二级标题名)
