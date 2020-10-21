# Based on https://github.com/cortexm/baremetal/blob/master/CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

# https://github.com/cortexm/baremetal
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER_ID GNU)
set(CMAKE_CXX_COMPILER_ID GNU)
set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3" CACHE STRING "")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3" CACHE STRING "")
set(CMAKE_C_FLAGS_RELEASE "-O3" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE STRING "")

# project name
project(miller_wireless_pedal C ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# we default to Release build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("-- Build Type: ${CMAKE_BUILD_TYPE}")

link_directories(${CMAKE_SOURCE_DIR}/linker/)

add_link_options(
    -Tble_app_blinky_gcc_nrf52.ld

    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -u _printf_float
    #-Wl,--cref
    -Wl,--check-sections
    -Wl,--gc-sections
    -Wl,--unresolved-symbols=report-all
    -Wl,--warn-common
    -Wl,--warn-section-align

    --specs=nano.specs
    --specs=nosys.specs
)

add_compile_options(
    -mcpu=cortex-m4
    -mthumb
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16

    -ffunction-sections
    -fdata-sections

    -fno-exceptions
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>

    -nostdlib
)

add_definitions(
    -DBOARD_SPARKFUN_NRF52840_MINI
    -DCONFIG_GPIO_AS_PINRESET
    -DFLOAT_ABI_HARD
    -DNRF_SD_BLE_API_VERSION=6
    -DS140
    -DSWI_DISABLE0
    -DSOFTDEVICE_PRESENT
    -DNRF52840_XXAA

    -D__HEAP_SIZE=8192
    -D__STACK_SIZE=8192
)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

# Bring in the Nordic SDK.
FetchContent_Declare(
  nRF5_SDK
  URL        https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK15209412b96.zip
  URL_HASH   MD5=6677511a17f5247686fbec73093f4c0c
  PATCH_COMMAND
    cp ${CMAKE_SOURCE_DIR}/patch/boards.h components/boards/ &&
    cp ${CMAKE_SOURCE_DIR}/patch/sparkfun_nrf52840_mini.h components/boards/
)

FetchContent_MakeAvailable(nRF5_SDK)
#message(${nrf5_sdk_SOURCE_DIR})

include_directories(
    config

    ${nrf5_sdk_SOURCE_DIR}/components
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_advertising
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_dtm
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_racp
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_ancs_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_ans_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_bas
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_bas_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_cscs
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_cts_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_dfu
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_dis
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_gls
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_hids
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_hrs
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_hrs_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_hts
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_ias
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_ias_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_lbs
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_lbs_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_lls
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_nus
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_nus_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_rscs
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_rscs_c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_tps
    ${nrf5_sdk_SOURCE_DIR}/components/ble/common
    ${nrf5_sdk_SOURCE_DIR}/components/ble/nrf_ble_gatt
    ${nrf5_sdk_SOURCE_DIR}/components/ble/nrf_ble_qwr
    ${nrf5_sdk_SOURCE_DIR}/components/ble/peer_manager
    ${nrf5_sdk_SOURCE_DIR}/components/boards
    ${nrf5_sdk_SOURCE_DIR}/components/drivers_nrf/usbd
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/atomic
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/atomic_fifo
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/atomic_flags
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/balloc
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/bootloader/ble_dfu
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/button
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/cli
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/crc16
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/crc32
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/crypto
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/csense
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/csense_drv
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/delay
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/ecc
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/experimental_section_vars
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/experimental_task_manager
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/fds
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/fstorage
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/gfx
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/gpiote
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/hardfault
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/hci
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/led_softblink
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/low_power_pwm
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/mem_manager
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/memobj
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/mpu
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/mutex
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/pwm
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/pwr_mgmt
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/queue
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/ringbuf
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/scheduler
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/sdcard
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/slip
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/sortlist
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/spi_mngr
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/stack_guard
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/strerror
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/svc
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/timer
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/twi_mngr
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/twi_sensor
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd/class/audio
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd/class/cdc
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd/class/cdc/acm
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd/class/hid
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd/class/hid/generic
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd/class/hid/kbd
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd/class/hid/mouse
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/usbd/class/msc
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/conn_hand_parser
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/conn_hand_parser/ac_rec_parser
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/conn_hand_parser/ble_oob_advdata_parse
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/conn_hand_parser/le_oob_rec_parser
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/connection_handover/ac_rec
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/connection_handover/ble_oob_advdata
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/connection_handover/ble_pair_lib
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/connection_handover/ble_pair_msg
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/connection_handover/common
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/connection_handover/ep_oob_rec
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/connection_handover/hs_rec
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/connection_handover/le_oob_rec
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/generic/message
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/generic/record
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/launchapp
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/parser/message
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/parser/record
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/text
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/ndef/uri
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t2t_lib
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t2t_lib/hal_t2t
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t2t_parser
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t4t_lib
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t4t_lib/hal_t4t
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t4t_parser/apdu
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t4t_parser/cc_file
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t4t_parser/hl_detection_procedure
    ${nrf5_sdk_SOURCE_DIR}/components/nfc/t4t_parser/tlv
    ${nrf5_sdk_SOURCE_DIR}/components/softdevice/common
    ${nrf5_sdk_SOURCE_DIR}/components/softdevice/s140/headers
    ${nrf5_sdk_SOURCE_DIR}/components/softdevice/s140/headers/nrf52
    ${nrf5_sdk_SOURCE_DIR}/components/toolchain/cmsis/include
    ${nrf5_sdk_SOURCE_DIR}/external/fprintf
    ${nrf5_sdk_SOURCE_DIR}/external/segger_rtt
    ${nrf5_sdk_SOURCE_DIR}/external/utf_converter
    ${nrf5_sdk_SOURCE_DIR}/integration/nrfx
    ${nrf5_sdk_SOURCE_DIR}/integration/nrfx/legacy
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/drivers/include
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/hal
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/mdk
)

add_executable(${PROJECT_NAME}
    main.c

    ${nrf5_sdk_SOURCE_DIR}/components/ble/ble_services/ble_lbs/ble_lbs.c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/common/ble_advdata.c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/common/ble_conn_params.c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/common/ble_conn_state.c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/common/ble_srv_common.c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/nrf_ble_gatt/nrf_ble_gatt.c
    ${nrf5_sdk_SOURCE_DIR}/components/ble/nrf_ble_qwr/nrf_ble_qwr.c
    ${nrf5_sdk_SOURCE_DIR}/components/boards/boards.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/atomic/nrf_atomic.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/atomic_fifo/nrf_atfifo.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/atomic_flags/nrf_atflags.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/balloc/nrf_balloc.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/button/app_button.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/experimental_section_vars/nrf_section_iter.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/hardfault/hardfault_implementation.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src/nrf_log_backend_rtt.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src/nrf_log_backend_serial.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src/nrf_log_backend_uart.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src/nrf_log_default_backends.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src/nrf_log_frontend.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src/nrf_log_str_formatter.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/memobj/nrf_memobj.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/ringbuf/nrf_ringbuf.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/scheduler/app_scheduler.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/strerror/nrf_strerror.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/timer/app_timer.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/app_error.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/app_error_handler_gcc.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/app_error_weak.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/app_util_platform.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/nrf_assert.c
    ${nrf5_sdk_SOURCE_DIR}/components/softdevice/common/nrf_sdh.c
    ${nrf5_sdk_SOURCE_DIR}/components/softdevice/common/nrf_sdh_ble.c
    ${nrf5_sdk_SOURCE_DIR}/components/softdevice/common/nrf_sdh_soc.c
    ${nrf5_sdk_SOURCE_DIR}/external/fprintf/nrf_fprintf.c
    ${nrf5_sdk_SOURCE_DIR}/external/fprintf/nrf_fprintf_format.c
    ${nrf5_sdk_SOURCE_DIR}/external/segger_rtt/SEGGER_RTT.c
    ${nrf5_sdk_SOURCE_DIR}/external/segger_rtt/SEGGER_RTT_printf.c
    ${nrf5_sdk_SOURCE_DIR}/external/segger_rtt/SEGGER_RTT_Syscalls_GCC.c
    ${nrf5_sdk_SOURCE_DIR}/external/utf_converter/utf.c
    ${nrf5_sdk_SOURCE_DIR}/integration/nrfx/legacy/nrf_drv_clock.c
    ${nrf5_sdk_SOURCE_DIR}/integration/nrfx/legacy/nrf_drv_uart.c
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/drivers/src/nrfx_clock.c
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/drivers/src/nrfx_gpiote.c
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/drivers/src/nrfx_power_clock.c
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/drivers/src/nrfx_uart.c
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/drivers/src/nrfx_uarte.c
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/drivers/src/prs/nrfx_prs.c
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/mdk/gcc_startup_nrf52840.S
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/mdk/system_nrf52840.c
)

set_target_properties(${PROJECT_NAME}
    # Force a .elf extension on the output file.
    PROPERTIES
        SUFFIX .elf

    # Place the resultant Elf into the top level directory.
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Shortcut for printing out the text/data/bss usage.
add_custom_target(size
    arm-none-eabi-size $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.hex
)

add_custom_target(dfu_package
    rm -f dfu-package.zip &&
    adafruit-nrfutil dfu genpkg --dev-type 0x0052 --sd-req 0x00B6 --application $<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.hex dfu-package.zip
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(bootload
    adafruit-nrfutil --verbose dfu serial --package dfu-package.zip -p ${SERIAL_PORT} -b 115200 --singlebank
    DEPENDS dfu_package
)
