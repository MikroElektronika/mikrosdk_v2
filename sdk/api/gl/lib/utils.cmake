include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

function(mikrosdk_install _targetName)
## INSTALL TARGET
    install(TARGETS ${_targetName}
        EXPORT ExportTestTarget
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
 ## INSTALL EXPORT FILE
    install(EXPORT ${_targetName}Target
        FILE ${_targetName}Targets.cmake
        NAMESPACE MikroSDK::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${_targetName})

    configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/${_targetName}Config.cmake.in
         "${CMAKE_CURRENT_BINARY_DIR}/" + ${_targetName} + "Config.cmake"
         INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${_targetName})

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/" + ${_targetName} + "ConfigVersion.cmake"
        VERSION ${CMAKE_PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion)
    install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/"+ ${_targetName} + "Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/" ${_targetName} + "ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${_targetName})