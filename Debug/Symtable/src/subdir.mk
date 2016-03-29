################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Symtable/src/Symtable.cpp \
../Symtable/src/Symtable_test.cpp 

OBJS += \
./Symtable/src/Symtable.o \
./Symtable/src/Symtable_test.o 

CPP_DEPS += \
./Symtable/src/Symtable.d \
./Symtable/src/Symtable_test.d 


# Each subdirectory must supply rules for building sources it contributes
Symtable/src/%.o: ../Symtable/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


