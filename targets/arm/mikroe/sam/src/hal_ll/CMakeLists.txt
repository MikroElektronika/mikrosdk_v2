## ./targets/arm/mikroe/ai_generated/sam/src/hal_ll/CMakeLists.txt
add_library(lib_hal_ll INTERFACE)

add_library(MikroSDK.HalLowLevel ALIAS lib_hal_ll)

target_link_libraries(lib_hal_ll INTERFACE
    MikroSDK.HalLowLevel.GPIO
)

get_files_recurse(${CMAKE_CURRENT_LIST_DIR}/../gpio CMAKE_FILES cmake)
foreach(cmakeFile ${CMAKE_FILES})
    include(${cmakeFile})
endforeach()

mikrosdk_install(MikroSDK.HalLowLevel)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel ${pmc_subimplementation}/hal_ll_pmc.h ../../include/hal_ll_target.h ../../include/hal_ll_pin_names.h ../../include/hal_ll_target_names.h)
