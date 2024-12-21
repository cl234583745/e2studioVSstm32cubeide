################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra/board/ra6m4_ek/board_init.c \
../ra/board/ra6m4_ek/board_leds.c 

C_DEPS += \
./ra/board/ra6m4_ek/board_init.d \
./ra/board/ra6m4_ek/board_leds.d 

OBJS += \
./ra/board/ra6m4_ek/board_init.o \
./ra/board/ra6m4_ek/board_leds.o 

SREC += \
ra6m4_backtrace.srec 

MAP += \
ra6m4_backtrace.map 


# Each subdirectory must supply rules for building sources it contributes
ra/board/ra6m4_ek/%.o: ../ra/board/ra6m4_ek/%.c
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM33 -D_RA_ORDINAL=1 -I"E:/RS_workspace/ra6m4_backtrace/src" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler/keil" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/Languages" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/Languages/en-US" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler/iar" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler/gcc" -I"E:/RS_workspace/ra6m4_backtrace/src" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/Languages/zh-CN" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler/ghs" -I"." -I"E:/RS_workspace/ra6m4_backtrace/ra/fsp/inc" -I"E:/RS_workspace/ra6m4_backtrace/ra/fsp/inc/api" -I"E:/RS_workspace/ra6m4_backtrace/ra/fsp/inc/instances" -I"E:/RS_workspace/ra6m4_backtrace/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"E:/RS_workspace/ra6m4_backtrace/ra_gen" -I"E:/RS_workspace/ra6m4_backtrace/ra_cfg/fsp_cfg/bsp" -I"E:/RS_workspace/ra6m4_backtrace/ra_cfg/fsp_cfg" -std=c99 -Wno-stringop-overflow -Wno-format-truncation --param=min-pagesize=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

