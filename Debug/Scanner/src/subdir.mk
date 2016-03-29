################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Scanner/src/Scanner.cpp \
../Scanner/src/TestScanner.cpp 

OBJS += \
./Scanner/src/Scanner.o \
./Scanner/src/TestScanner.o 

CPP_DEPS += \
./Scanner/src/Scanner.d \
./Scanner/src/TestScanner.d 


# Each subdirectory must supply rules for building sources it contributes
Scanner/src/%.o: ../Scanner/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


