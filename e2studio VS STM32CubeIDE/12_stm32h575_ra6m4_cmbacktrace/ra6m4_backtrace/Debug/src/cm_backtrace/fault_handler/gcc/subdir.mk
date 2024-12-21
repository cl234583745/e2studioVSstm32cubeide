################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../src/cm_backtrace/fault_handler/gcc/cmb_fault.S 

OBJS += \
./src/cm_backtrace/fault_handler/gcc/cmb_fault.o 

SREC += \
ra6m4_backtrace.srec 

S_UPPER_DEPS += \
./src/cm_backtrace/fault_handler/gcc/cmb_fault.d 

MAP += \
ra6m4_backtrace.map 


# Each subdirectory must supply rules for building sources it contributes
src/cm_backtrace/fault_handler/gcc/%.o: ../src/cm_backtrace/fault_handler/gcc/%.S
	$(file > $@.in,-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-strict-aliasing -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -gdwarf-4 -x assembler-with-cpp -D_RENESAS_RA_ -D_RA_CORE=CM33 -D_RA_ORDINAL=1 -I"E:/RS_workspace/ra6m4_backtrace/src" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler/keil" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/Languages" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/Languages/en-US" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler/iar" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler/gcc" -I"E:/RS_workspace/ra6m4_backtrace/src" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/Languages/zh-CN" -I"E:/RS_workspace/ra6m4_backtrace/src/cm_backtrace/fault_handler/ghs" -I"." -I"E:/RS_workspace/ra6m4_backtrace/ra/fsp/inc" -I"E:/RS_workspace/ra6m4_backtrace/ra/fsp/inc/api" -I"E:/RS_workspace/ra6m4_backtrace/ra/fsp/inc/instances" -I"E:/RS_workspace/ra6m4_backtrace/ra/arm/CMSIS_6/CMSIS/Core/Include" -I"E:/RS_workspace/ra6m4_backtrace/ra_gen" -I"E:/RS_workspace/ra6m4_backtrace/ra_cfg/fsp_cfg/bsp" -I"E:/RS_workspace/ra6m4_backtrace/ra_cfg/fsp_cfg" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

