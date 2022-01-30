cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(print_GFX_graphicstest_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
       print_GFX_graphicstest print_GFX_graphicstest.cpp
                       print_GFX_ILI9341.cpp    # pring_GFX_ILI9341ÇégópÇ∑ÇÈèÍçáÇÕí«â¡ÇµÇƒÇ≠ÇæÇ≥Ç¢
                       yama_2_GFX.cpp
)

target_link_libraries(print_GFX_graphicstest
                       pico_stdlib
                       hardware_spi
)

pico_enable_stdio_usb(print_GFX_graphicstest 0)
pico_enable_stdio_uart(print_GFX_graphicstest 1)

pico_add_extra_outputs(print_GFX_graphicstest)

