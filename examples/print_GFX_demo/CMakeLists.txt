cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(print_GFX_demo.cpp_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
       print_GFX_demo    print_GFX_demo.cpp
                         print_GFX_ILI9341.cpp       #print_GFX_ILI9341を使う場合は追加してください
                         print_GFX_GFXcanvas16.cpp   #print_GFX_GFXcanvas16を使う場合は追加してください
                         yama_2_GFX.cpp
)

target_link_libraries(   print_GFX_demo
                         pico_stdlib
                         hardware_spi
)

pico_enable_stdio_usb(print_GFX_demo 0)
pico_enable_stdio_uart(print_GFX_demo 1)

pico_add_extra_outputs(print_GFX_demo)

