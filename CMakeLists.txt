cmake_minimum_required(VERSION 3.12) 

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pwm C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pwm_rgb_fade
        pwm_rgb_fade.c
        )

# pull in common dependencies and additional pwm hardware support
target_link_libraries(pwm_rgb_fade pico_stdlib hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(pwm_rgb_fade)

# add url via pico_set_program_url
example_auto_set_url(pwm_rgb_fade)
