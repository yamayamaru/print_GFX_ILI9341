cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(random_raspberry_32px_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
       random_raspberry_32px random_raspberry_32px.cpp 
                       yama_2_GFX.cpp                # yama_2_GFX‚ðŽg‚¤‚Æ‚«‚É’Ç‰Á‚·‚é
                       print_GFX_GFXcanvas16.cpp     # print_GFX_GFXcanvas16‚ðŽg‚¤‚Æ‚«‚É’Ç‰Á‚·‚é
)

target_link_libraries(random_raspberry_32px
                       pico_stdlib
                       hardware_spi
)

pico_enable_stdio_usb(random_raspberry_32px 1)
pico_enable_stdio_uart(random_raspberry_32px 0)

pico_add_extra_outputs(random_raspberry_32px)

