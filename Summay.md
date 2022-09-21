# lam
gdb attach

、
    root@asp-1a:~ >cat /proc/9259/stack
    [<0>] futex_wait_queue_me+0xb4/0x110
    [<0>] futex_wait+0xe9/0x240
    [<0>] do_futex+0x178/0xbc0
    [<0>] __x64_sys_futex+0x146/0x1c0
    [<0>] do_syscall_64+0x33/0x40
    [<0>] entry_SYSCALL_64_after_hwframe+0x44/0xa9![image](https://user-images.githubusercontent.com/33516039/191402658-ef67b98d-10f9-4e59-bc56-aa25cb551d0c.png)
、


ftrace
pstree -t查看进程下的所有线程
