################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.c" \
"../Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.c" \

C_SRCS += \
../Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.c \
../Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.c \

OBJS += \
./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o \
./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o \

C_DEPS += \
./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.d \
./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.d \

OBJS_QUOTED += \
"./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o" \
"./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o" \

C_DEPS_QUOTED += \
"./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.d" \
"./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.d" \

OBJS_OS_FORMAT += \
./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o \
./Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o: ../Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/gsc_scheduler/periodic_tasks/periodic_tasks_exec.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o: ../Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/gsc_scheduler/periodic_tasks/periodic_tasks_init.o"
	@echo 'Finished building: $<'
	@echo ' '


