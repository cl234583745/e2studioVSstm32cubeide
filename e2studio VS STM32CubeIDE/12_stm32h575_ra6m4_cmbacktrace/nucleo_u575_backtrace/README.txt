-gdwarf-4


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


Jerry.Chen@WTNB-6719 MINGW64 /e/ST_workspace/nucleo_u575_backtrace/Debug
$ ./addr2line.exe -e nucleo_u575_backtrace.elf -afpiC 080010fe 08001136 08001158 08001176 0800120e 08001742
0x080010fe: fault_test_by_div0 at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:57
0x08001136: func_c at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:68
0x08001158: func_b at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:74
0x08001176: func_a at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:80
0x0800120e: main at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Src/main.c:190 (discriminator 1)
0x08001742: Reset_Handler at E:/ST_workspace/nucleo_u575_backtrace/Debug/../Core/Startup/startup_stm32u575z
itxq.s:100

