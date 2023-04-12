cstag:

    [http://cscope.sourceforge.net]
下载cscope

2.安装:
     tar -zxf cscope-xx.x.tar.gz 
     cd cscope-xx.x 
     ./configure 
     make 
     make install
    然后把contib/xcscope/目录下的cscope-indexer复制到PATH目录比如/usr/local/bin 

find . -name "*.h" -o -name "*.c" -o -name "*.cc" -o -name "*.sh" -o -name "*.cpp"  -o -name "*.hpp" > cscope.files
 cscope -Rbkq -i cscope.files


进入vim c文件
cs add /var/fpwork/amingliao/uphwapi/cscope.out /var/fpwork/amingliao/uphwapi/


cstags -R *

Ctrl+]   Ctrl+t

1. cscope -Rbqk



1或者g  —— 查找这个定义
2或者d  —— 查找被这个函数调用的函数（们）
3或者c  —— 查找调用这个函数的函数（们）

Ctrl+D 退出cscope界面

https://ratel.blog.csdn.net/article/details/121187199 -fsanitize=address

比如常用的有（选项c）查找调用此函数的地方，（选项d）查找此函数调用的地方，（选项g）查找函数定义。

find : 查询一个模式                   (Usage: find a|c|d|e|f|g|i|s|t name)
       a: Find assignments to thissymbol
       c: Find functions calling thisfunctiond: Find functions called bythisfunctione: Find thisegrep pattern
       f: Find thisfile
       g: Find thisdefinition
       i: Find files #including this files: Find thisC symbol
       t: Find thistext string
