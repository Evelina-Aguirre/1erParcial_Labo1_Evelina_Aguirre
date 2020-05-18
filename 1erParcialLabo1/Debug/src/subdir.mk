################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/1erParcialLabo1.c \
../src/ArrayEmployees.c \
../src/Reports.c \
../src/Sectors.c \
../src/utn.c 

OBJS += \
./src/1erParcialLabo1.o \
./src/ArrayEmployees.o \
./src/Reports.o \
./src/Sectors.o \
./src/utn.o 

C_DEPS += \
./src/1erParcialLabo1.d \
./src/ArrayEmployees.d \
./src/Reports.d \
./src/Sectors.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


