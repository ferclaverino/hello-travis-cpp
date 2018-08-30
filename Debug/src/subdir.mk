################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataValue.cpp \
../src/Index.cpp \
../src/Series.cpp \
../src/main.cpp 

OBJS += \
./src/DataValue.o \
./src/Index.o \
./src/Series.o \
./src/main.o 

CPP_DEPS += \
./src/DataValue.d \
./src/Index.d \
./src/Series.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


