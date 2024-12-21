Debug level		Default (-g)
Debug format	dwarf-4



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



Jerry.Chen@WTNB-6719 MINGW64 /e/RS_workspace/ra6m4_backtrace/Debug
$ ./addr2line.exe -e ra6m4_backtrace.elf -afpiC 00000e3e 00000e76 00000e98 00000eb6 00000f04 00001042 000023dc
0x00000e3e: fault_test_by_div0 at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:78
0x00000e76: func_c at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:89
0x00000e98: func_b at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:95
0x00000eb6: func_a at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:101
0x00000f04: hal_entry at E:\RS_workspace\ra6m4_backtrace\Debug/../src/hal_entry.c:215
0x00001042: main at E:\RS_workspace\ra6m4_backtrace\Debug/../ra_gen/main.c:6
0x000023dc: Reset_Handler at E:\RS_workspace\ra6m4_backtrace\Debug/../ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/startup.c:55



