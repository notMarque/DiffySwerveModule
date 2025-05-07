# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(MotorTesting C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

#DRV8245HW libraries
aux_source_directory(./DRV8245HW DRV8245HW)
aux_source_directory(./EncoderLib EncoderLib)
aux_source_directory(. PROJECT_SOURCES)

# Add executable. Default name is the project name, version 0.1

add_executable(MotorTesting 
    MotorTesting.cpp
    ${PROJECT_SOURCES}
    ${DRV8245HW}
    ${EncoderLib})

pico_generate_pio_header(MotorTesting ${CMAKE_CURRENT_LIST_DIR}./EncoderLib/quadrature_encoder_substep.pio)

target_include_directories(MotorTesting PRIVATE ./EncoderLib/quadrature_encoder_substep)
target_include_directories(MotorTesting PRIVATE ./DRV8245HW/DRV8245HW)

pico_set_program_name(MotorTesting "MotorTesting")
pico_set_program_version(MotorTesting "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(MotorTesting 0)
pico_enable_stdio_usb(MotorTesting 1)

# Add the standard library to the build
target_link_libraries(
        MotorTesting
        pico_stdlib
        pico_multicore 
        hardware_gpio 
        hardware_pwm
        hardware_watchdog
        hardware_pio
        hardware_i2c)

# Add the standard include files to the build
target_include_directories(MotorTesting PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)
pico_enable_stdio_usb(MotorTesting 1)
pico_add_extra_outputs(MotorTesting)

