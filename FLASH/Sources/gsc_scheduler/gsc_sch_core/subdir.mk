################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.c" \
"../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.c" \
"../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.c" \

C_SRCS += \
../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.c \
../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.c \
../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.c \

OBJS += \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.o \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.o \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o \

C_DEPS += \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.d \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.d \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.d \

OBJS_QUOTED += \
"./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.o" \
"./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.o" \
"./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o" \

C_DEPS_QUOTED += \
"./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.d" \
"./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.d" \
"./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.d" \

OBJS_OS_FORMAT += \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.o \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.o \
./Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.o: ../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.o: ../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_cfg.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o: ../Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/gsc_scheduler/gsc_sch_core/gsc_sch_core_tick_isr.o"
	@echo 'Finished building: $<'
	@echo ' '


