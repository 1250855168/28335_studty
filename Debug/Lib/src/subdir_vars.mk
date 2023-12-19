################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../Lib/src/DSP2833x_ADC_cal.asm \
../Lib/src/DSP2833x_CSMPasswords.asm \
../Lib/src/DSP2833x_CodeStartBranch.asm \
../Lib/src/DSP2833x_DBGIER.asm \
../Lib/src/DSP2833x_DisInt.asm \
../Lib/src/DSP2833x_usDelay.asm 

C_SRCS += \
../Lib/src/DSP2833x_Adc.c \
../Lib/src/DSP2833x_CpuTimers.c \
../Lib/src/DSP2833x_DMA.c \
../Lib/src/DSP2833x_DefaultIsr.c \
../Lib/src/DSP2833x_ECan.c \
../Lib/src/DSP2833x_ECap.c \
../Lib/src/DSP2833x_EPwm.c \
../Lib/src/DSP2833x_EQep.c \
../Lib/src/DSP2833x_GlobalVariableDefs.c \
../Lib/src/DSP2833x_Gpio.c \
../Lib/src/DSP2833x_I2C.c \
../Lib/src/DSP2833x_Mcbsp.c \
../Lib/src/DSP2833x_MemCopy.c \
../Lib/src/DSP2833x_PieCtrl.c \
../Lib/src/DSP2833x_PieVect.c \
../Lib/src/DSP2833x_SWPrioritizedDefaultIsr.c \
../Lib/src/DSP2833x_SWPrioritizedPieVect.c \
../Lib/src/DSP2833x_Sci.c \
../Lib/src/DSP2833x_Spi.c \
../Lib/src/DSP2833x_SysCtrl.c \
../Lib/src/DSP2833x_Xintf.c 

C_DEPS += \
./Lib/src/DSP2833x_Adc.d \
./Lib/src/DSP2833x_CpuTimers.d \
./Lib/src/DSP2833x_DMA.d \
./Lib/src/DSP2833x_DefaultIsr.d \
./Lib/src/DSP2833x_ECan.d \
./Lib/src/DSP2833x_ECap.d \
./Lib/src/DSP2833x_EPwm.d \
./Lib/src/DSP2833x_EQep.d \
./Lib/src/DSP2833x_GlobalVariableDefs.d \
./Lib/src/DSP2833x_Gpio.d \
./Lib/src/DSP2833x_I2C.d \
./Lib/src/DSP2833x_Mcbsp.d \
./Lib/src/DSP2833x_MemCopy.d \
./Lib/src/DSP2833x_PieCtrl.d \
./Lib/src/DSP2833x_PieVect.d \
./Lib/src/DSP2833x_SWPrioritizedDefaultIsr.d \
./Lib/src/DSP2833x_SWPrioritizedPieVect.d \
./Lib/src/DSP2833x_Sci.d \
./Lib/src/DSP2833x_Spi.d \
./Lib/src/DSP2833x_SysCtrl.d \
./Lib/src/DSP2833x_Xintf.d 

OBJS += \
./Lib/src/DSP2833x_ADC_cal.obj \
./Lib/src/DSP2833x_Adc.obj \
./Lib/src/DSP2833x_CSMPasswords.obj \
./Lib/src/DSP2833x_CodeStartBranch.obj \
./Lib/src/DSP2833x_CpuTimers.obj \
./Lib/src/DSP2833x_DBGIER.obj \
./Lib/src/DSP2833x_DMA.obj \
./Lib/src/DSP2833x_DefaultIsr.obj \
./Lib/src/DSP2833x_DisInt.obj \
./Lib/src/DSP2833x_ECan.obj \
./Lib/src/DSP2833x_ECap.obj \
./Lib/src/DSP2833x_EPwm.obj \
./Lib/src/DSP2833x_EQep.obj \
./Lib/src/DSP2833x_GlobalVariableDefs.obj \
./Lib/src/DSP2833x_Gpio.obj \
./Lib/src/DSP2833x_I2C.obj \
./Lib/src/DSP2833x_Mcbsp.obj \
./Lib/src/DSP2833x_MemCopy.obj \
./Lib/src/DSP2833x_PieCtrl.obj \
./Lib/src/DSP2833x_PieVect.obj \
./Lib/src/DSP2833x_SWPrioritizedDefaultIsr.obj \
./Lib/src/DSP2833x_SWPrioritizedPieVect.obj \
./Lib/src/DSP2833x_Sci.obj \
./Lib/src/DSP2833x_Spi.obj \
./Lib/src/DSP2833x_SysCtrl.obj \
./Lib/src/DSP2833x_Xintf.obj \
./Lib/src/DSP2833x_usDelay.obj 

ASM_DEPS += \
./Lib/src/DSP2833x_ADC_cal.d \
./Lib/src/DSP2833x_CSMPasswords.d \
./Lib/src/DSP2833x_CodeStartBranch.d \
./Lib/src/DSP2833x_DBGIER.d \
./Lib/src/DSP2833x_DisInt.d \
./Lib/src/DSP2833x_usDelay.d 

OBJS__QUOTED += \
"Lib\src\DSP2833x_ADC_cal.obj" \
"Lib\src\DSP2833x_Adc.obj" \
"Lib\src\DSP2833x_CSMPasswords.obj" \
"Lib\src\DSP2833x_CodeStartBranch.obj" \
"Lib\src\DSP2833x_CpuTimers.obj" \
"Lib\src\DSP2833x_DBGIER.obj" \
"Lib\src\DSP2833x_DMA.obj" \
"Lib\src\DSP2833x_DefaultIsr.obj" \
"Lib\src\DSP2833x_DisInt.obj" \
"Lib\src\DSP2833x_ECan.obj" \
"Lib\src\DSP2833x_ECap.obj" \
"Lib\src\DSP2833x_EPwm.obj" \
"Lib\src\DSP2833x_EQep.obj" \
"Lib\src\DSP2833x_GlobalVariableDefs.obj" \
"Lib\src\DSP2833x_Gpio.obj" \
"Lib\src\DSP2833x_I2C.obj" \
"Lib\src\DSP2833x_Mcbsp.obj" \
"Lib\src\DSP2833x_MemCopy.obj" \
"Lib\src\DSP2833x_PieCtrl.obj" \
"Lib\src\DSP2833x_PieVect.obj" \
"Lib\src\DSP2833x_SWPrioritizedDefaultIsr.obj" \
"Lib\src\DSP2833x_SWPrioritizedPieVect.obj" \
"Lib\src\DSP2833x_Sci.obj" \
"Lib\src\DSP2833x_Spi.obj" \
"Lib\src\DSP2833x_SysCtrl.obj" \
"Lib\src\DSP2833x_Xintf.obj" \
"Lib\src\DSP2833x_usDelay.obj" 

C_DEPS__QUOTED += \
"Lib\src\DSP2833x_Adc.d" \
"Lib\src\DSP2833x_CpuTimers.d" \
"Lib\src\DSP2833x_DMA.d" \
"Lib\src\DSP2833x_DefaultIsr.d" \
"Lib\src\DSP2833x_ECan.d" \
"Lib\src\DSP2833x_ECap.d" \
"Lib\src\DSP2833x_EPwm.d" \
"Lib\src\DSP2833x_EQep.d" \
"Lib\src\DSP2833x_GlobalVariableDefs.d" \
"Lib\src\DSP2833x_Gpio.d" \
"Lib\src\DSP2833x_I2C.d" \
"Lib\src\DSP2833x_Mcbsp.d" \
"Lib\src\DSP2833x_MemCopy.d" \
"Lib\src\DSP2833x_PieCtrl.d" \
"Lib\src\DSP2833x_PieVect.d" \
"Lib\src\DSP2833x_SWPrioritizedDefaultIsr.d" \
"Lib\src\DSP2833x_SWPrioritizedPieVect.d" \
"Lib\src\DSP2833x_Sci.d" \
"Lib\src\DSP2833x_Spi.d" \
"Lib\src\DSP2833x_SysCtrl.d" \
"Lib\src\DSP2833x_Xintf.d" 

ASM_DEPS__QUOTED += \
"Lib\src\DSP2833x_ADC_cal.d" \
"Lib\src\DSP2833x_CSMPasswords.d" \
"Lib\src\DSP2833x_CodeStartBranch.d" \
"Lib\src\DSP2833x_DBGIER.d" \
"Lib\src\DSP2833x_DisInt.d" \
"Lib\src\DSP2833x_usDelay.d" 

ASM_SRCS__QUOTED += \
"../Lib/src/DSP2833x_ADC_cal.asm" \
"../Lib/src/DSP2833x_CSMPasswords.asm" \
"../Lib/src/DSP2833x_CodeStartBranch.asm" \
"../Lib/src/DSP2833x_DBGIER.asm" \
"../Lib/src/DSP2833x_DisInt.asm" \
"../Lib/src/DSP2833x_usDelay.asm" 

C_SRCS__QUOTED += \
"../Lib/src/DSP2833x_Adc.c" \
"../Lib/src/DSP2833x_CpuTimers.c" \
"../Lib/src/DSP2833x_DMA.c" \
"../Lib/src/DSP2833x_DefaultIsr.c" \
"../Lib/src/DSP2833x_ECan.c" \
"../Lib/src/DSP2833x_ECap.c" \
"../Lib/src/DSP2833x_EPwm.c" \
"../Lib/src/DSP2833x_EQep.c" \
"../Lib/src/DSP2833x_GlobalVariableDefs.c" \
"../Lib/src/DSP2833x_Gpio.c" \
"../Lib/src/DSP2833x_I2C.c" \
"../Lib/src/DSP2833x_Mcbsp.c" \
"../Lib/src/DSP2833x_MemCopy.c" \
"../Lib/src/DSP2833x_PieCtrl.c" \
"../Lib/src/DSP2833x_PieVect.c" \
"../Lib/src/DSP2833x_SWPrioritizedDefaultIsr.c" \
"../Lib/src/DSP2833x_SWPrioritizedPieVect.c" \
"../Lib/src/DSP2833x_Sci.c" \
"../Lib/src/DSP2833x_Spi.c" \
"../Lib/src/DSP2833x_SysCtrl.c" \
"../Lib/src/DSP2833x_Xintf.c" 


