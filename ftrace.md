### Enable ftrace（自行添加flag）:   
cat /sys/kernel/debug/tracing/trace\
tasket -p pid/tid\
**Enable the ftrace:**
```C
    system("echo 1 >  /sys/kernel/debug/tracing/events/syscalls/sys_enter_sched_setaffinity/enable");
    //system("echo 1 >  /sys/kernel/debug/tracing/events/syscalls/sys_enter_sched_getaffinity/enable");
    system("echo affinity not changed > /sys/kernel/debug/tracing/trace_marker");
    //system("echo 1 > /sys/kernel/tracing/events/enable");
    char command[100]={"ps -Leo pid,comm |grep Disp_3| awk '{print $1}'"};
    char output[10];
 
    // 构造要执行的命令
// snprintf(command, 256, "ps -Leo pid,comm |grep Disp_2| awk '{print $1}'");
    // 执行命令并获取输出
    FILE *fp = popen(command, "r");
    // 读取输出并移除换行符
    if (fgets(output, 10, fp) != NULL) {
        output[strcspn(output, "\n")] = '\0';
    }
 
    // 关闭文件指针
    pclose(fp);
    system("echo 1 > /sys/kernel/debug/tracing/tracing_on");
    // 打印获取到的 PID
    LOG(Warning,"Terry Dispatcher3 的 PID 为：%s\n", output);
 
    // 将 PID 转换为整数并进行其他操作
    int pid = atoi(output);
    char command2[100];
 
    sprintf(command2, "taskset -p %d", pid);
    fp = popen(command2, "r");
 
    char output2[256];
    while (fgets(output2, sizeof(output2), fp) != NULL) {
        LOG(Warning,"Terry6 Taskset Output: %s", output2);
    }
 
    pclose(fp);
 
   system("echo affinity changed > /sys/kernel/debug/tracing/trace_marker");
   LOG(Warning, "sleeping done, sending UP_PLATFORM_READY_REQ");
   system("echo 0 > /sys/kernel/debug/tracing/tracing_on");
```
