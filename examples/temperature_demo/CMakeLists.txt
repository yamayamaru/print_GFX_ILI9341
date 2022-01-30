cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(temperature_demo_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
       temperature_demo temperature_demo.cpp 
                       yama_2_GFX.cpp                # yama_2_GFX‚ðŽg‚¤‚Æ‚«‚É’Ç‰Á‚·‚é
                       print_GFX_GFXcanvas16.cpp     # print_GFX_GFXcanvas16‚ðŽg‚¤‚Æ‚«‚É’Ç‰Á‚·‚é
)

target_link_libraries(temperature_demo
                       pico_stdlib
                       hardware_spi
                       hardware_adc
)

pico_enable_stdio_usb(temperature_demo 1)
pico_enable_stdio_uart(temperature_demo 0)

pico_add_extra_outputs(temperature_demo)

