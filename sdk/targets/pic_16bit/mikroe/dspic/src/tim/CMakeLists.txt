## ./mikroe/dspic/src/tim/CMakeLists.txt
set(hal_ll_def_list "")

if(${MCU_NAME} MATCHES "(ds)?PIC")
    list(APPEND hal_ll_def_list "__dspic__")
else()
    list(APPEND hal_ll_def_list "__family_not_supported__")
endif()

list(APPEND hal_ll_def_list ${MCU_NAME})

string(LENGTH ${MCU_NAME} MEMAKE_MCU_NAME_LENGTH)
MATH(EXPR BEGIN_INDEX "${MEMAKE_MCU_NAME_LENGTH}-3")
string(SUBSTRING ${MCU_NAME} ${BEGIN_INDEX} 3 MCU_NAME_LAST_3)

## BEGIN TIM
if (${MCU_NAME} MATCHES "(ds)?PIC24F[01V][68104][68K][KML][M1234][012][0124]")
    set(tim_implementation "implementation_2")
else()
    set(tim_implementation "implementation_1")
endif()
## END TIM

list(APPEND hal_ll_def_list "MACRO_USAGE_TIM")

if(${MCU_NAME} MATCHES "^(ds)?PIC30")
    list(APPEND hal_ll_def_list "TIM_DIV_CONST=250UL")
else()
    list(APPEND hal_ll_def_list "TIM_DIV_CONST=500UL")
endif()

if(${MCU_NAME} MATCHES "^(ds)?PIC(24|33)(.+MU|EP.+MC[258]0[2346]$|.+GA[123467]|.+GU[8]|EP.+G[PS][2578]|.+G[BCM]|.+GA[123467]|.+K[A][3].[124]$|.+D[A][12][01][06]$)")
    list(APPEND hal_ll_def_list "HAL_LL_TIM_IMP_2")
else()
    list(APPEND hal_ll_def_list "HAL_LL_TIM_IMP_1")
endif()

mikrosdk_add_library(lib_hal_ll_tim MikroSDK.HalLowLevel.TIM
    ${tim_implementation}/hal_ll_tim.c

    ../../include/hal_ll_target.h
    ../../include/hal_ll_slrcon_map.h
    ../../include/hal_ll_odcon_map.h
    ../../include/tim/hal_ll_tim.h
    ../../include/tim/hal_ll_tim_pin_map.h
)

target_compile_definitions(lib_hal_ll_tim PUBLIC
    ${hal_ll_def_list}
)

target_link_libraries(lib_hal_ll_tim PUBLIC
    MikroC.Core
    MikroSDK.HalLowLevel.PPS
    MikroSDK.HalLowLevelCore
    MikroSDK.HalLowLevelCommon
)

string(TOLOWER ${MCU_NAME} MCU_NAME_LOWER)
target_include_directories(lib_hal_ll_tim
    PRIVATE
        ../../include
        ../../include/tim
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include/tim>
        $<INSTALL_INTERFACE:include/hal_ll_port>
        $<INSTALL_INTERFACE:include/${MCU_NAME_LOWER}>
)

mikrosdk_install(MikroSDK.HalLowLevel.TIM)
install_headers(${CMAKE_INSTALL_PREFIX}/include/hal_ll_port MikroSDK.HalLowLevel.TIM ../../include/tim/hal_ll_tim.h ../../include/tim/hal_ll_tim_pin_map.h)
