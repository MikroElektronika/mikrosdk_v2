cmake_minimum_required(VERSION 3.19)

project(test_default_gpio_dual_core LANGUAGES C ASM)

include(mikroeUtils)

add_subdirectory(core_m85)
add_subdirectory(core_m33ef)
