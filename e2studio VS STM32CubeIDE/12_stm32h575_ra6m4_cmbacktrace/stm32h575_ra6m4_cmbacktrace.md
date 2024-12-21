十二、e2studio VS STM32CubeIDE之栈回溯cmbacktrace
===
[TOC]

# 一、概述/目的
- 我们分享过[十四、从0开始卷出一个新项目之瑞萨RZN2L之栈回溯](https://mp.weixin.qq.com/s/faMyh4RBUyfY41wQOOb4aw?token=1942811917&lang=zh_CN)，相关资料可跳转过去查看
- 我们继续分享通用mcu cm33内核stm32u575和瑞萨ra6m4的栈回溯cmbacktrace的例程源码
- 为了快速定位hardfault，进一步介绍栈回溯的知识

# 二、注意或限制
- 栈回溯打印的地址必须与可执行文件(例如elf)匹配，即elf文件和固件版本一一对应
- 目前提供的源码只针对裸机，rtos需要另外修改
- 栈回溯与优化等级和调试等级有关系
- 栈回溯不是万能的，例如栈溢出 

# 三、stm32u575 cmbacktrace
- cm内核移植比较简单，直接看结果，源码可去github gitee下载测试
- 修改stack和text地址
- 修改优化等级none
- addr2line有报错，可修改debug formart -gdwarf-4
- 输出日志如下：
```
hello world!
date:Dec 20 2024
time:12:44:05
file:../Core/Src/main.c
func:main,line:178
hello world!
fault_test_by_div0

Firmware name: CmBacktrace, hardware version: V1.0.0, software version: V0.1.0
Fault on interrupt or bare metal(no OS) environment
stack_start_addr=20000000, stack_size=786432, stack_pointer=200bffa8
===== Thread stack information =====
  addr: 200bffa8    data: 200bffc0
  addr: 200bffac    data: 00000000
  addr: 200bffb0    data: 0000000a
  addr: 200bffb4    data: e000ed14
  addr: 200bffb8    data: 200bffc0
  addr: 200bffbc    data: 08001137
  addr: 200bffc0    data: ffffffff
  addr: 200bffc4    data: 00000001
  addr: 200bffc8    data: 200bffd0
  addr: 200bffcc    data: 08001159
  addr: 200bffd0    data: 00000000
  addr: 200bffd4    data: 00000001
  addr: 200bffd8    data: 200bffe0
  addr: 200bffdc    data: 08001177
  addr: 200bffe0    data: 08008678
  addr: 200bffe4    data: 00000001
  addr: 200bffe8    data: 200bfff8
  addr: 200bffec    data: 0800120f
  addr: 200bfff0    data: 080086a8
  addr: 200bfff4    data: 000000b2
  addr: 200bfff8    data: 00000000
  addr: 200bfffc    data: 08001743
====================================
=================== Registers information ====================
  R0 : 0000000a  R1 : 00000040  R2 : 0000000a  R3 : 00000000
  R12: 0000000a  LR : 08001137  PC : 080010fe  PSR: 41000000
==============================================================
Usage fault is caused by Indicates a divide by zero has taken place (can be set only if DIV_0_TRP is set)
Show more call stack info by run: addr2line -e CmBacktrace.elf -afpiC 080010fe 08001136 08001158 08001176 0800120e 08001742 
```

- addr2line报错日志，可修改debug等级和格式

```
Jerry.Chen@WTNB-6719 MINGW64 /e/ST_workspace/nucleo_u575_backtrace/Debug
$ ./addr2line.exe -e nucleo_u575_backtrace.elf -afpiC 080010fe 08001136 08001158 08001176 0800120e 08001742
0x080010fe: BFD: Dwarf Error: found dwarf version '5', this reader only handles
version 2, 3 and 4 information.
fault_test_by_div0 at ??:?
0x08001136: BFD: Dwarf Error: found dwarf version '0', this reader only handles
version 2, 3 and 4 information.
func_c at main.c:?
0x08001158: BFD: Dwarf Error: found dwarf version '7424', this reader only handl
es version 2, 3 and 4 information.
func_b at main.c:?
0x08001176: BFD: Dwarf Error: found dwarf version '0', this reader only handles
version 2, 3 and 4 information.
func_a at main.c:?
0x0800120e: BFD: Dwarf Error: found dwarf version '0', this reader only handles
version 2, 3 and 4 information.
main at ??:?
0x08001742: BFD: Dwarf Error: found dwarf version '0', this reader only handles
version 2, 3 and 4 information.
LoopForever at startup_stm32u575zitxq.o:?
```
- 修改debug等级和格式之后的结果
```
Jerry.Chen@WTNB-6719 MINGW64 /e/ST_workspace/nucleo_u575_backtrace/Debug
$ ./addr2line.exe -e nucleo_u575_backtrace.elf -afpiC 080010fe 08001136 08001158 08001176 0800120e 08001742
0x080010fe: fault_test_by_div0 at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:57
0x08001136: func_c at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:68
0x08001158: func_b at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:74
0x08001176: func_a at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:80
0x0800120e: main at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:190 (discriminator 1)
0x08001742: Reset_Handler at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Startup/startup_stm32u575z
itxq.s:100
```



# 四、瑞萨ra6m4 cmbacktrace
- cm内核移植比较简单，直接看结果，源码可去github gitee下载测试
- 修改stack和text地址
- 修改优化等级none
- addr2line有报错，可修改
  Debug level		Default (-g)
  Debug format	dwarf-4
- 输出日志如下：

```
date:Dec 20 2024
time:14:21:19
file:../src/hal_entry.c
func:hal_entry,line:204
hello world!
PI=3.141593
fault_test_by_div0

Firmware name: CmBacktrace, hardware version: V1.0.0, software version: V0.1.0
Fault on interrupt or bare metal(no OS) environment
stack_start_addr=20001750, stack_size=4096, stack_pointer=200026e0
===== Thread stack information =====
  addr: 200026e0    data: 200026f8
  addr: 200026e4    data: 00000000
  addr: 200026e8    data: 0000000a
  addr: 200026ec    data: e000ed14
  addr: 200026f0    data: 200026f8
  addr: 200026f4    data: 00000e77
  addr: 200026f8    data: 000000ff
  addr: 200026fc    data: 00000001
  addr: 20002700    data: 20002708
  addr: 20002704    data: 00000e99
  addr: 20002708    data: 00000000
  addr: 2000270c    data: 00000001
  addr: 20002710    data: 20002718
  addr: 20002714    data: 00000eb7
  addr: 20002718    data: 00006850
  addr: 2000271c    data: 00000001
  addr: 20002720    data: 20002730
  addr: 20002724    data: 00000f05
  addr: 20002728    data: 00006864
  addr: 2000272c    data: 000000cc
  addr: 20002730    data: 20001750
  addr: 20002734    data: 40490fda
  addr: 20002738    data: 20002740
  addr: 2000273c    data: 00001043
  addr: 20002740    data: 20002748
  addr: 20002744    data: 000023dd
  addr: 20002748    data: 00000000
  addr: 2000274c    data: ffffffff
====================================
=================== Registers information ====================
  R0 : 0000000a  R1 : 20000758  R2 : 0000000a  R3 : 00000000
  R12: c01243f6  LR : 00000e77  PC : 00000e3e  PSR: 49100000
==============================================================
Usage fault is caused by Indicates a divide by zero has taken place (can be set only if DIV_0_TRP is set)
Show more call stack info by run: addr2line -e CmBacktrace.elf -afpiC 00000e3e 00000e76 00000e98 00000eb6 00000f04 00001042 000023dc 
```
- addr2line输出结果
```
Jerry.Chen@WTNB-6719 MINGW64 /e/RS_workspace/ra6m4_backtrace/Debug
$ ./addr2line.exe -e ra6m4_backtrace.elf -afpiC 00000e3e 00000e76 00000e98 00000eb6 00000f04 00001042 000023dc
0x00000e3e: fault_test_by_div0 at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:78
0x00000e76: func_c at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:89
0x00000e98: func_b at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:95
0x00000eb6: func_a at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:101
0x00000f04: hal_entry at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:215
0x00001042: main at E:\RS_workspace\ra6m4_backtrace\Debug/../ra_gen/main.c:6
0x000023dc: Reset_Handler at E:\RS_workspace\ra6m4_backtrace\Debug/../ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.c:55
```

# 五、总结
- cmbacktrace移植比较简单，主要修改stack、text地址
- 栈回溯是有一些限制的
- 栈回溯功能加入到产品中也是非常有意义的
- 栈回溯其实就是入栈的反向，了解栈回溯可以深入了解到c代码是如何运行的




