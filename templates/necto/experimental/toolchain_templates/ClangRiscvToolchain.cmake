%SDK_VARIABLE_VALUES%
# set CMAKE_SYSTEM_NAME to define build as CMAKE_CROSSCOMPILING
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

# specify cross compilers and tools
set(CMAKE_C_COMPILER "%C_COMPILER%" CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER "%CXX_COMPILER%" CACHE INTERNAL "")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

file(TO_CMAKE_PATH "%MIKROSDK_PATH%" MIKROSDK_PATH)
file(TO_CMAKE_PATH "%MIKROC_CORE_PATH%" MIKROC_CORE_PATH)

set(MIKROSDK_ROOT_PATH ${MIKROSDK_PATH})
set(MIKROC_CORE_ROOT_PATH ${MIKROC_CORE_PATH})
#append to cmake_prefix_path
list(APPEND CMAKE_PREFIX_PATH ${MIKROSDK_ROOT_PATH})
list(APPEND CMAKE_PREFIX_PATH ${MIKROC_CORE_ROOT_PATH})

list(APPEND CMAKE_MODULE_PATH %CMAKE_MODULE_PATH_VALUE%)


# set(FLAGS --target=riscv32imac-unknown-elf -Wl,--no-relax -Wl,--gc-sections,--print-memory-usage -nostartfiles -lc -lgcc -ffunction-sections -fdata-sections -fno-common -fmessage-length=0 -specs=nano.specs -specs=nosys.specs)
set(FLAGS --target=riscv32-unknown-elf -march=rv32imac -mabi=ilp32 -fomit-frame-pointer -Wno-int-conversion -Wno-incompatible-function-pointer-types -Wno-implicit-function-declaration -Wl,--no-relax -Wl,--gc-sections,--print-memory-usage -nostartfiles -ggdb -ffunction-sections -fdata-sections -fno-common -fmessage-length=0 -specs=nosys.specs)
message(INFO ": FLAGS --target=riscv32-unknown-elf -march=rv32imac -mabi=ilp32 -fomit-frame-pointer -Wno-int-conversion -Wno-incompatible-function-pointer-types -Wno-implicit-function-declaration -Wl,--no-relax -Wl,--gc-sections,--print-memory-usage -nostartfiles -ggdb -ffunction-sections -fdata-sections -fno-common -fmessage-length=0 -specs=nosys.specs")
# add compiler option flags
add_compile_options( ${FLAGS})
# add link option flags
add_link_options(${FLAGS})

%SDK_SETUP_BUILD_VALUE%

if (SDK_SETUP_BUILD)
    add_link_options(-T "%LINKER_SCRIPT%")
endif()
