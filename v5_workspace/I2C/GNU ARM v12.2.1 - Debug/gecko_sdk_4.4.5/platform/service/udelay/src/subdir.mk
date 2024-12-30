################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5/platform/service/udelay/src/sl_udelay.c 

S_UPPER_SRCS += \
E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5/platform/service/udelay/src/sl_udelay_armv6m_gcc.S 

OBJS += \
./gecko_sdk_4.4.5/platform/service/udelay/src/sl_udelay.o \
./gecko_sdk_4.4.5/platform/service/udelay/src/sl_udelay_armv6m_gcc.o 

C_DEPS += \
./gecko_sdk_4.4.5/platform/service/udelay/src/sl_udelay.d 


# Each subdirectory must supply rules for building sources it contributes
gecko_sdk_4.4.5/platform/service/udelay/src/sl_udelay.o: E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5/platform/service/udelay/src/sl_udelay.c gecko_sdk_4.4.5/platform/service/udelay/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -std=c99 '-DDEBUG=1' '-DDEBUG_EFM=1' '-DEFR32BG13P632F512GM48=1' '-DSL_BOARD_NAME="BRD4104A"' '-DSL_BOARD_REV="A02"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=38400000' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\Admin\SimplicityStudio\v5_workspace\I2C\config" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\I2C\autogen" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\I2C" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/Device/SiliconLabs/EFR32BG13P/Include" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//app/common/util/app_log" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/common/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//hardware/board/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/CMSIS/Core/Include" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//hardware/driver/configuration_over_swo/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/driver/debug/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/device_init/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/emdrv/dmadrv/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/emdrv/common/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/emlib/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/driver/i2cspm/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/iostream/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/common/toolchain/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/system/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/sleeptimer/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/udelay/inc" -Os -Wall -Wextra -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv4-sp-d16 -mfloat-abi=softfp --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"gecko_sdk_4.4.5/platform/service/udelay/src/sl_udelay.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

gecko_sdk_4.4.5/platform/service/udelay/src/sl_udelay_armv6m_gcc.o: E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5/platform/service/udelay/src/sl_udelay_armv6m_gcc.S gecko_sdk_4.4.5/platform/service/udelay/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m4 -mthumb -I"C:\Users\Admin\SimplicityStudio\v5_workspace\I2C\config" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\I2C\autogen" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\I2C" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/Device/SiliconLabs/EFR32BG13P/Include" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//app/common/util/app_log" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/common/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//hardware/board/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/CMSIS/Core/Include" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//hardware/driver/configuration_over_swo/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/driver/debug/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/device_init/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/emdrv/dmadrv/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/emdrv/common/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/emlib/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/driver/i2cspm/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/iostream/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/common/toolchain/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/system/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/sleeptimer/inc" -I"E:/THIOT/gecko_sdk_4_4_5/gecko_sdk_4_4_5//platform/service/udelay/inc" '-DDEBUG_EFM=1' '-DEFR32BG13P632F512GM48=1' '-DSL_BOARD_NAME="BRD4104A"' '-DSL_BOARD_REV="A02"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=38400000' '-DSL_COMPONENT_CATALOG_PRESENT=1' -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -imacrossl_gcc_preinclude.h -c -x assembler-with-cpp -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

