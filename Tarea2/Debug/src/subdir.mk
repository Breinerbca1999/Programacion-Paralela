################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/prodmatrizvectorSecu.cpp \
../src/prodmatrizvectorpall.cpp 

C_SRCS += \
../src/Suma_Vectores.c 

OBJS += \
./src/Suma_Vectores.o \
./src/prodmatrizvectorSecu.o \
./src/prodmatrizvectorpall.o 

CPP_DEPS += \
./src/prodmatrizvectorSecu.d \
./src/prodmatrizvectorpall.d 

C_DEPS += \
./src/Suma_Vectores.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	mpicc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	mpic++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


