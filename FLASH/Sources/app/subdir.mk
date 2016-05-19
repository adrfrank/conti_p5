################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/app/LIN_common.c" \
"../Sources/app/LIN_mstr_core.c" \
"../Sources/app/LIN_mstr_hal.c" \
"../Sources/app/LIN_mstr_il.c" \
"../Sources/app/LIN_mstr_network.c" \
"../Sources/app/LIN_mstr_sched.c" \
"../Sources/app/LIN_slave_core.c" \
"../Sources/app/LIN_slave_hal.c" \
"../Sources/app/LIN_slave_il.c" \
"../Sources/app/LIN_slave_network.c" \
"../Sources/app/RGB_LEDs.c" \
"../Sources/app/UART_hal.c" \
"../Sources/app/app_commander.c" \
"../Sources/app/app_slave_actions.c" \

C_SRCS += \
../Sources/app/LIN_common.c \
../Sources/app/LIN_mstr_core.c \
../Sources/app/LIN_mstr_hal.c \
../Sources/app/LIN_mstr_il.c \
../Sources/app/LIN_mstr_network.c \
../Sources/app/LIN_mstr_sched.c \
../Sources/app/LIN_slave_core.c \
../Sources/app/LIN_slave_hal.c \
../Sources/app/LIN_slave_il.c \
../Sources/app/LIN_slave_network.c \
../Sources/app/RGB_LEDs.c \
../Sources/app/UART_hal.c \
../Sources/app/app_commander.c \
../Sources/app/app_slave_actions.c \

OBJS += \
./Sources/app/LIN_common.o \
./Sources/app/LIN_mstr_core.o \
./Sources/app/LIN_mstr_hal.o \
./Sources/app/LIN_mstr_il.o \
./Sources/app/LIN_mstr_network.o \
./Sources/app/LIN_mstr_sched.o \
./Sources/app/LIN_slave_core.o \
./Sources/app/LIN_slave_hal.o \
./Sources/app/LIN_slave_il.o \
./Sources/app/LIN_slave_network.o \
./Sources/app/RGB_LEDs.o \
./Sources/app/UART_hal.o \
./Sources/app/app_commander.o \
./Sources/app/app_slave_actions.o \

C_DEPS += \
./Sources/app/LIN_common.d \
./Sources/app/LIN_mstr_core.d \
./Sources/app/LIN_mstr_hal.d \
./Sources/app/LIN_mstr_il.d \
./Sources/app/LIN_mstr_network.d \
./Sources/app/LIN_mstr_sched.d \
./Sources/app/LIN_slave_core.d \
./Sources/app/LIN_slave_hal.d \
./Sources/app/LIN_slave_il.d \
./Sources/app/LIN_slave_network.d \
./Sources/app/RGB_LEDs.d \
./Sources/app/UART_hal.d \
./Sources/app/app_commander.d \
./Sources/app/app_slave_actions.d \

OBJS_QUOTED += \
"./Sources/app/LIN_common.o" \
"./Sources/app/LIN_mstr_core.o" \
"./Sources/app/LIN_mstr_hal.o" \
"./Sources/app/LIN_mstr_il.o" \
"./Sources/app/LIN_mstr_network.o" \
"./Sources/app/LIN_mstr_sched.o" \
"./Sources/app/LIN_slave_core.o" \
"./Sources/app/LIN_slave_hal.o" \
"./Sources/app/LIN_slave_il.o" \
"./Sources/app/LIN_slave_network.o" \
"./Sources/app/RGB_LEDs.o" \
"./Sources/app/UART_hal.o" \
"./Sources/app/app_commander.o" \
"./Sources/app/app_slave_actions.o" \

C_DEPS_QUOTED += \
"./Sources/app/LIN_common.d" \
"./Sources/app/LIN_mstr_core.d" \
"./Sources/app/LIN_mstr_hal.d" \
"./Sources/app/LIN_mstr_il.d" \
"./Sources/app/LIN_mstr_network.d" \
"./Sources/app/LIN_mstr_sched.d" \
"./Sources/app/LIN_slave_core.d" \
"./Sources/app/LIN_slave_hal.d" \
"./Sources/app/LIN_slave_il.d" \
"./Sources/app/LIN_slave_network.d" \
"./Sources/app/RGB_LEDs.d" \
"./Sources/app/UART_hal.d" \
"./Sources/app/app_commander.d" \
"./Sources/app/app_slave_actions.d" \

OBJS_OS_FORMAT += \
./Sources/app/LIN_common.o \
./Sources/app/LIN_mstr_core.o \
./Sources/app/LIN_mstr_hal.o \
./Sources/app/LIN_mstr_il.o \
./Sources/app/LIN_mstr_network.o \
./Sources/app/LIN_mstr_sched.o \
./Sources/app/LIN_slave_core.o \
./Sources/app/LIN_slave_hal.o \
./Sources/app/LIN_slave_il.o \
./Sources/app/LIN_slave_network.o \
./Sources/app/RGB_LEDs.o \
./Sources/app/UART_hal.o \
./Sources/app/app_commander.o \
./Sources/app/app_slave_actions.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/app/LIN_common.o: ../Sources/app/LIN_common.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_common.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_common.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_mstr_core.o: ../Sources/app/LIN_mstr_core.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_mstr_core.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_mstr_core.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_mstr_hal.o: ../Sources/app/LIN_mstr_hal.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_mstr_hal.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_mstr_hal.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_mstr_il.o: ../Sources/app/LIN_mstr_il.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_mstr_il.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_mstr_il.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_mstr_network.o: ../Sources/app/LIN_mstr_network.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_mstr_network.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_mstr_network.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_mstr_sched.o: ../Sources/app/LIN_mstr_sched.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_mstr_sched.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_mstr_sched.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_slave_core.o: ../Sources/app/LIN_slave_core.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_slave_core.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_slave_core.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_slave_hal.o: ../Sources/app/LIN_slave_hal.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_slave_hal.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_slave_hal.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_slave_il.o: ../Sources/app/LIN_slave_il.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_slave_il.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_slave_il.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/LIN_slave_network.o: ../Sources/app/LIN_slave_network.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/LIN_slave_network.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/LIN_slave_network.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/RGB_LEDs.o: ../Sources/app/RGB_LEDs.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/RGB_LEDs.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/RGB_LEDs.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/UART_hal.o: ../Sources/app/UART_hal.c
	@echo 'Building file: $<'
	@echo 'Executing target #22 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/UART_hal.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/UART_hal.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/app_commander.o: ../Sources/app/app_commander.c
	@echo 'Building file: $<'
	@echo 'Executing target #23 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/app_commander.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/app_commander.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app/app_slave_actions.o: ../Sources/app/app_slave_actions.c
	@echo 'Building file: $<'
	@echo 'Executing target #24 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app/app_slave_actions.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app/app_slave_actions.o"
	@echo 'Finished building: $<'
	@echo ' '


