cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_DEOPTIMIZED_DEBUG 1)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
#set(PICO_SDK_PATH "/Users/timax/Development/pi_pico/pico-sdk") # <-- SDK PATH

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(as5600_example C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# dwm_pico_AS5600 library files
aux_source_directory(./lib/dwm_pico_AS5600 dwm_pico_AS5600) #<-- Add library files

aux_source_directory(. PROJECT_SOURCES)

# Add executable. Default name is the project name
add_executable(as5600_example as5600_example.c ${PROJECT_SOURCES} ${dwm_pico_AS5600}) #<-- Add library files to executable

target_include_directories(as5600_example PRIVATE
    ./lib/dwm_pico_AS5600 #<-- Include subdirectories
    )

pico_set_program_name(as5600_example "as5600_example")

pico_enable_stdio_uart(as5600_example 1)
pico_enable_stdio_usb(as5600_example 1)

# Add the standard library to the build
target_link_libraries(as5600_example pico_stdlib hardware_i2c)

pico_add_extra_outputs(as5600_example)