cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(random_text.cpp_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
       random_text    random_text.cpp
                         print_GFX_ILI9341.cpp    # pring_GFX_ILI9341ÇégópÇ∑ÇÈèÍçáÇÕí«â¡ÇµÇƒÇ≠ÇæÇ≥Ç¢
                         yama_2_GFX.cpp
)

target_link_libraries(   random_text
                         pico_stdlib
                         hardware_spi
)

pico_enable_stdio_usb(random_text 0)
pico_enable_stdio_uart(random_text 1)

pico_add_extra_outputs(random_text)

