################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5/platform/service/power_manager/src/sl_power_manager.c \
E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5/platform/service/power_manager/src/sl_power_manager_debug.c \
E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5/platform/service/power_manager/src/sl_power_manager_hal_s2.c 

OBJS += \
./simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager.o \
./simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager_debug.o \
./simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager_hal_s2.o 

C_DEPS += \
./simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager.d \
./simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager_debug.d \
./simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager_hal_s2.d 


# Each subdirectory must supply rules for building sources it contributes
simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager.o: E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5/platform/service/power_manager/src/sl_power_manager.c simplicity_sdk_2024.6.2/platform/service/power_manager/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c18 '-DEFR32MG21A020F1024IM32=1' '-DSL_APP_PROPERTIES=1' '-DBOOTLOADER_APPLOADER=1' '-DSL_BOARD_NAME="BRD4180B"' '-DSL_BOARD_REV="A03"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=38400000' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DCMSIS_NVIC_VIRTUAL=1' '-DCMSIS_NVIC_VIRTUAL_HEADER_FILE="cmsis_nvic_virtual.h"' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DSL_MEMORY_POOL_LIGHT=1' '-DSL_CODE_COMPONENT_POWER_MANAGER=power_manager' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSL_CODE_COMPONENT_CORE=core' '-DSL_CODE_COMPONENT_SLEEPTIMER=sleeptimer' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\autogen" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\config" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\config\btconf" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/Device/SiliconLabs/EFR32MG21/Include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_assert" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_log" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_timer" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_timer/bm" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/common/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/bgcommon/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/bgstack/ll/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//hardware/board/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/bootloader" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/bootloader/api" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/clock_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/clock_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/CMSIS/Core/Include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//hardware/driver/configuration_over_swo/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/driver/debug/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/device_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/dmadrv/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/dmadrv/inc/s2_signals" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/common/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emlib/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/bluetooth/common/gatt_service_device_information" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/bluetooth/common/in_place_ota_dfu" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/interrupt_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/interrupt_manager/inc/arm" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/iostream/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/config" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//util/third_party/mbedtls/include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//util/third_party/mbedtls/library" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/profiler/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/mpu/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/nvm3/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/power_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_psa_driver/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/common" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/ble" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/ieee802154" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/wmbus" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/zwave" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/sidewalk" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/pa-conversions" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/pa-conversions/efr32xg21" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_pti" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_rf_path" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/se_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/se_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/common/toolchain/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/system/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/sleeptimer/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_protocol_crypto/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/udelay/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager_debug.o: E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5/platform/service/power_manager/src/sl_power_manager_debug.c simplicity_sdk_2024.6.2/platform/service/power_manager/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c18 '-DEFR32MG21A020F1024IM32=1' '-DSL_APP_PROPERTIES=1' '-DBOOTLOADER_APPLOADER=1' '-DSL_BOARD_NAME="BRD4180B"' '-DSL_BOARD_REV="A03"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=38400000' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DCMSIS_NVIC_VIRTUAL=1' '-DCMSIS_NVIC_VIRTUAL_HEADER_FILE="cmsis_nvic_virtual.h"' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DSL_MEMORY_POOL_LIGHT=1' '-DSL_CODE_COMPONENT_POWER_MANAGER=power_manager' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSL_CODE_COMPONENT_CORE=core' '-DSL_CODE_COMPONENT_SLEEPTIMER=sleeptimer' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\autogen" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\config" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\config\btconf" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/Device/SiliconLabs/EFR32MG21/Include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_assert" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_log" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_timer" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_timer/bm" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/common/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/bgcommon/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/bgstack/ll/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//hardware/board/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/bootloader" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/bootloader/api" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/clock_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/clock_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/CMSIS/Core/Include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//hardware/driver/configuration_over_swo/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/driver/debug/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/device_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/dmadrv/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/dmadrv/inc/s2_signals" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/common/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emlib/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/bluetooth/common/gatt_service_device_information" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/bluetooth/common/in_place_ota_dfu" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/interrupt_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/interrupt_manager/inc/arm" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/iostream/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/config" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//util/third_party/mbedtls/include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//util/third_party/mbedtls/library" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/profiler/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/mpu/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/nvm3/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/power_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_psa_driver/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/common" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/ble" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/ieee802154" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/wmbus" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/zwave" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/sidewalk" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/pa-conversions" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/pa-conversions/efr32xg21" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_pti" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_rf_path" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/se_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/se_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/common/toolchain/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/system/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/sleeptimer/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_protocol_crypto/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/udelay/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager_debug.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager_hal_s2.o: E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5/platform/service/power_manager/src/sl_power_manager_hal_s2.c simplicity_sdk_2024.6.2/platform/service/power_manager/src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c18 '-DEFR32MG21A020F1024IM32=1' '-DSL_APP_PROPERTIES=1' '-DBOOTLOADER_APPLOADER=1' '-DSL_BOARD_NAME="BRD4180B"' '-DSL_BOARD_REV="A03"' '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' '-DHFXO_FREQ=38400000' '-DSL_COMPONENT_CATALOG_PRESENT=1' '-DCMSIS_NVIC_VIRTUAL=1' '-DCMSIS_NVIC_VIRTUAL_HEADER_FILE="cmsis_nvic_virtual.h"' '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' '-DSL_MEMORY_POOL_LIGHT=1' '-DSL_CODE_COMPONENT_POWER_MANAGER=power_manager' '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' '-DSL_CODE_COMPONENT_CORE=core' '-DSL_CODE_COMPONENT_SLEEPTIMER=sleeptimer' '-DSLI_RADIOAES_REQUIRES_MASKING=1' -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\autogen" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\config" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty\config\btconf" -I"C:\Users\Admin\SimplicityStudio\v5_workspace\bt_soc_empty" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/Device/SiliconLabs/EFR32MG21/Include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_assert" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_log" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_timer" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/common/util/app_timer/bm" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/common/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/bgcommon/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//protocol/bluetooth/bgstack/ll/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//hardware/board/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/bootloader" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/bootloader/api" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/clock_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/clock_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/CMSIS/Core/Include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//hardware/driver/configuration_over_swo/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/driver/debug/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/device_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/dmadrv/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/dmadrv/inc/s2_signals" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/common/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emlib/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/bluetooth/common/gatt_service_device_information" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//app/bluetooth/common/in_place_ota_dfu" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/interrupt_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/interrupt_manager/inc/arm" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/iostream/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/config" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/config/preset" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_mbedtls_support/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//util/third_party/mbedtls/include" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//util/third_party/mbedtls/library" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/memory_manager/profiler/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/mpu/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/emdrv/nvm3/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/power_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_psa_driver/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/common" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/ble" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/ieee802154" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/wmbus" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/zwave" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/protocol/sidewalk" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/pa-conversions" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/pa-conversions/efr32xg21" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_power_manager_init" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_pti" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/radio/rail_lib/plugin/rail_util_rf_path" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/se_manager/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/se_manager/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/common/toolchain/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/system/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/sleeptimer/inc" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/security/sl_component/sl_protocol_crypto/src" -I"E:/THIOT/simplicity_sdk_suite_v2024_6_2/simplicity_sdk_5//platform/service/udelay/inc" -Os -Wall -Wextra -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mcmse --specs=nano.specs -c -fmessage-length=0 -MMD -MP -MF"simplicity_sdk_2024.6.2/platform/service/power_manager/src/sl_power_manager_hal_s2.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


