# Based on https://github.com/cortexm/baremetal/blob/master/CMakeLists.txt
cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_FLAGS_DEBUG "-O0 -g3" CACHE STRING "")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3" CACHE STRING "")
set(CMAKE_C_FLAGS_RELEASE "-O3" CACHE STRING "")
set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE STRING "")

# project name
project(pedal_debug)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# we default to Release build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("-- Build Type: ${CMAKE_BUILD_TYPE}")

# Make sure we can find Qt.
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5
    COMPONENTS Core Widgets bluetooth
    REQUIRED
    PATHS /usr/local/Cellar/qt5/5.15.0)

add_compile_options(
    -ffunction-sections
    -fdata-sections

    -fno-exceptions
)

include_directories(
    include
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Bluetooth_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
    main.cpp

    bluetooth_helper.cpp
    ui.cpp

    # HACKY?  We need to include the headers as source for AUTOMOC to work?
    include/bluetooth_helper.h
    include/ui.h
)

target_link_libraries(${PROJECT_NAME}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Bluetooth_LIBRARIES}
)
