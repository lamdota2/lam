# C语言笔记
## _The Last Markdown Editor, Ever_

- [sizeof计算](#sizeof结构体，数据对齐)
- [ASAN使用](#ASAN检测非法访问，多次free)

## sizeof结构体，数据对齐
```C
    typedef struct {
             char a[13];
             int b;
    } eth_hdr_t;
    sizeof(eth_hdr_t) = 20
 ```
sizeof 联合体union，联合的本质是一个成员相互重叠的结构，某一时刻只能使用一个成员。

```c++
typedef union {
         char a[13];
         int b;
} eth_hdr_t;
sizeof(eth_hdr_t) = 16

sizeof 指针，64位cpu为8 byte,32位为4 Byte

	1. p是指针，*p是它指向的内容
	*p++和*(p++)等价
	int a[5], p=a; *(p+3)执行第三个元素
```
[Coredump 调试案例](https://blog.csdn.net/qq_45527937/article/details/124559660)

## ASAN检测非法访问，多次free
增加编译选项-fsanitize=address


