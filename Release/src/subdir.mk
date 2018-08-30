################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DataValue.cpp \
../src/Index.cpp \
../src/Series.cpp \
../src/hello-travis-cpp.cpp \
../src/main.cpp 

OBJS += \
./src/DataValue.o \
./src/Index.o \
./src/Series.o \
./src/hello-travis-cpp.o \
./src/main.o 

CPP_DEPS += \
./src/DataValue.d \
./src/Index.d \
./src/Series.d \
./src/hello-travis-cpp.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


