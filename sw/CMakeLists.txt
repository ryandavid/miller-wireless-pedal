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
project(miller_wireless_pedal)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# we default to Release build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("-- Build Type: ${CMAKE_BUILD_TYPE}")

add_link_options(
    -T${CMAKE_SOURCE_DIR}/linker/blinky_gcc_nrf52.ld

    -Wl,--gc-sections

    -specs=nano.specs

    -mcpu=cortex-m4
    -mthumb
    -mabi=aapcs
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
)

add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>

    $<$<COMPILE_LANGUAGE:CXX>:-Wold-style-cast>
    $<$<COMPILE_LANGUAGE:CXX>:-Wsuggest-override>

    #-Werror
    -Wall
    -Wextra
    #-Wcast-align
    #-Wconversion
    #-Wsign-conversion

    -Wshadow
    -Wlogical-op

    -Wsuggest-final-types
    -Wsuggest-final-methods

    -Wno-expansion-to-defined



    # Debugging.
    -DNDEBUG
    -D_DEBUG
    -DBOARD_SPARKFUN_NRF52840_MINI
    -DUNICODE
    -D_UNICODE
    -DBSP_DEFINES_ONLY
    -DCONFIG_GPIO_AS_PINRESET
    -DFLOAT_ABI_HARD
    -DNRF52840_XXAA
    -DDCONFIG_NFCT_PINS_AS_GPIOS

    # Optimization
    -ffunction-sections
    -fdata-sections
    -mlong-calls
    -fno-math-errno

    -mcpu=cortex-m4
    -mthumb
    -mabi=aapcs
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

# Bring in the Nordic SDK.
FetchContent_Declare(
  nRF5_SDK
  URL       https://www.nordicsemi.com/-/media/Software-and-other-downloads/SDKs/nRF5/Binaries/nRF5SDK1702d674dde.zip
  URL_HASH  MD5=a04e2f76e712689aa1dff13969696af3
  PATCH_COMMAND
    cp ${CMAKE_SOURCE_DIR}/patch/boards.h components/boards/ &&
    cp ${CMAKE_SOURCE_DIR}/patch/sparkfun_nrf52840_mini.h components/boards/
)

FetchContent_MakeAvailable(nRF5_SDK)
#message(${nrf5_sdk_SOURCE_DIR})

include_directories(
    config

    ${nrf5_sdk_SOURCE_DIR}/components
    ${nrf5_sdk_SOURCE_DIR}/components/boards
    ${nrf5_sdk_SOURCE_DIR}/components/drivers_nrf/nrf_soc_nosd
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/atomic
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/balloc
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/bsp
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/delay
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/delay
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/experimental_log
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/experimental_log/src
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/experimental_memobj
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/experimental_section_vars
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/fifo
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/strerror
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/uart
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util
    ${nrf5_sdk_SOURCE_DIR}/components/toolchain/cmsis/include
    ${nrf5_sdk_SOURCE_DIR}/integration/nrfx
    ${nrf5_sdk_SOURCE_DIR}/integration/nrfx/legacy
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/drivers/include
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/hal
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/mdk
)
add_executable(${PROJECT_NAME}
    main.c

    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/mdk/gcc_startup_nrf52840.S
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src/nrf_log_frontend.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/log/src/nrf_log_str_formatter.c
    ${nrf5_sdk_SOURCE_DIR}/components/boards/boards.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/app_error.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/app_error_handler_gcc.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/app_error_weak.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/app_util_platform.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/util/nrf_assert.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/atomic/nrf_atomic.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/balloc/nrf_balloc.c
    ${nrf5_sdk_SOURCE_DIR}/external/fprintf/nrf_fprintf.c
    ${nrf5_sdk_SOURCE_DIR}/external/fprintf/nrf_fprintf_format.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/memobj/nrf_memobj.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/ringbuf/nrf_ringbuf.c
    ${nrf5_sdk_SOURCE_DIR}/components/libraries/strerror/nrf_strerror.c
    ${nrf5_sdk_SOURCE_DIR}/modules/nrfx/soc/nrfx_atomic.c
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
    COMMAND arm-none-eabi-objcopy -O ihex -R .eeprom -R .fuse -R .lock -R .signature $<TARGET_FILE:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>/$<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.hex
)

add_custom_target(dfu_package
    adafruit-nrfutil dfu genpkg --sd-req 0xFFFE --dev-type 0x0052 --application $<TARGET_FILE_BASE_NAME:${PROJECT_NAME}>.hex dfu-package.zip
    DEPENDS ${PROJECT_NAME}
)

add_custom_target(bootload
    adafruit-nrfutil --verbose dfu serial --package dfu-package.zip -p ${SERIAL_PORT} -b 115200 --singlebank --touch 1200
    DEPENDS dfu_package
)
