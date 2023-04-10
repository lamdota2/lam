**[TOC]**
- [markdown guide](#guide)
- [调查hang和常见进程问题](#调查hang和常见进程问题)
- [gdb attach](#gdb-attach)
- [ftrace](#ftrace)
- [查看进程下的所有线程](#查看进程下的所有线程)
- [vim插件&sed](#vim插件&sed)

### guide
http://marxi.co/

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

root@asp-1a:/opt/usr >./bin/gdb attach 9259
(gdb) bt
#0  0x00007ffff6fc0196 in ?? () from target:/usr/lib64/libc.so.6
#1  0x00007ffff7031a79 in ?? () from target:/usr/lib64/libc.so.6
#2  0x00007ffff7031b49 in syslog () from target:/usr/lib64/libc.so.6
#3  0x00007ffff76f66e9 in copyPrintToJournal () from target:/opt/lib/libCCSRT.so
#4  0x00007ffff76f796f in AaSysLogPrint () from target:/opt/lib/libCCSRT.so
#5  0x000000000040def4 in ?? ()
#6  0x0000000000412b15 in ?? ()
#7  0x0000000000409e98 in ?? ()
#8  0x0000000000405e59 in ?? ()
#9  0x00007ffff6f65e0a in __libc_start_main () from target:/usr/lib64/libc.so.6
#10 0x0000000000405efa in ?? ()![image](https://user-images.githubusercontent.com/33516039/194984044-b5a1fce1-22b2-4895-977b-c44bc30d868b.png)

```
### ftrace

### 查看进程下的所有线程
pstree -t
ps aux -T

https://ecotrust-canada.github.io/markdown-toc/

### vim插件&sed
1.批量替换关键字

sed -i "s/AAEMSERVICES_EMDISPMON_DBG/AAEMSERVICES_EMDISPMON_ERR/g" ` grep AAEMSERVICES_EMDISPMON_DBG -rl  .`

2.vim代码插件

ctags & cscope

### 生成标题
其实只要把"[TOC]"换成下方所示语法即可

- [显示在目录上的一级标题名](#实际一级标题名)
  - [显示在目录上的二级标题名](#实际二级标题名)
