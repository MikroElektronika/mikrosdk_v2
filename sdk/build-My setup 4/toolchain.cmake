set(CORE_NAME "RISCV" CACHE STRING "" FORCE)
set(DEFINE_DEVICE "USE_STDPERIPH_DRIVER" CACHE STRING "" FORCE)
set(HAS_MIKROBUS "true" CACHE STRING "" FORCE)
set(MCU_NAME "GD32VF103VBT6" CACHE STRING "" FORCE)
set(_MSDK_BOARD_NAME_ "BOARD_UNI_DS_V8" CACHE STRING "" FORCE)
set(_MSDK_DIP_SOCKET_TYPE_ "" CACHE STRING "" FORCE)
set(_MSDK_HAL_LOW_LEVEL_TARGET_ "mikroe" CACHE STRING "" FORCE)
set(_MSDK_MCU_CARD_NAME_ "MCU_CARD_FOR_RISC_V" CACHE STRING "" FORCE)
set(_MSDK_PACKAGE_NAME_ "LQFP" CACHE STRING "" FORCE)
set(TOOLCHAIN_ID "xpack-riscv-none-embed-gcc" CACHE STRING "" FORCE)
set(OSC "108" CACHE STRING "" FORCE)

# set CMAKE_SYSTEM_NAME to define build as CMAKE_CROSSCOMPILING
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

# specify cross compilers and tools
set(CMAKE_C_COMPILER "C:/NECTOStudio/NECTOStudio/compilers/RISCV/xpack-riscv-none-embed-gcc/bin/riscv-none-embed-gcc.exe" CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER "C:/NECTOStudio/NECTOStudio/compilers/RISCV/xpack-riscv-none-embed-gcc/bin/riscv-none-embed-g++.exe" CACHE INTERNAL "")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
# specify compiler and linker flags
set(FLAGS -Wl,--no-relax -Wl,--gc-sections,--print-memory-usage -nostartfiles -lc -lgcc -march=rv32imac -mabi=ilp32 -mcmodel=medlow -ffunction-sections -fdata-sections -fno-common -fmessage-length=0 -specs=nano.specs -specs=nosys.specs)

# add compiler option flags
add_compile_options(${FLAGS})
# add link option flags
add_link_options(${FLAGS})

# add linker script
if (SDK_SETUP_BUILD)
    add_link_options(-T "%LINKER_SCRIPT%")
endif()

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

file(TO_CMAKE_PATH "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/.meproject/setup/Debug/lib/cmake" MIKROSDK_PATH)
file(TO_CMAKE_PATH "D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/.meproject/setup/Debug/lib/cmake" MIKROC_CORE_PATH)

set(MIKROSDK_ROOT_PATH ${MIKROSDK_PATH})
set(MIKROC_CORE_ROOT_PATH ${MIKROC_CORE_PATH})
#append to cmake_prefix_path
list(APPEND CMAKE_PREFIX_PATH ${MIKROSDK_ROOT_PATH})
list(APPEND CMAKE_PREFIX_PATH ${MIKROC_CORE_ROOT_PATH})

list(APPEND CMAKE_MODULE_PATH "C:/Users/Software/AppData/Local/MIKROE/NECTOStudio2/cmake;C:/NECTOStudio/NECTOStudio/compilers/RISCV/xpack-riscv-none-embed-gcc/core/cmake;D:/gitlab/gitlab sdk/necto_sdk_2.10.0/sdk/.meproject/setup/Debug/cmake;")
