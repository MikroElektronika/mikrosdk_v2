## ./api/CMakeLists.txt
if (${MSDK_BUILD_TFT_MODULES})
    add_subdirectory(gl)
    add_subdirectory(tp)
    add_subdirectory(vtft)
endif()

add_subdirectory(log)
