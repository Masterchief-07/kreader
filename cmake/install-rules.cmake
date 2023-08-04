if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/kreader-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package kreader)

install(
    DIRECTORY
    include/
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT kreader_Development
)

install(
    TARGETS kreader_kreader
    EXPORT kreaderTargets
    RUNTIME #
    COMPONENT kreader_Runtime
    LIBRARY #
    COMPONENT kreader_Runtime
    NAMELINK_COMPONENT kreader_Development
    ARCHIVE #
    COMPONENT kreader_Development
    INCLUDES #
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    kreader_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(kreader_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${kreader_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT kreader_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${kreader_INSTALL_CMAKEDIR}"
    COMPONENT kreader_Development
)

install(
    EXPORT kreaderTargets
    NAMESPACE kreader::
    DESTINATION "${kreader_INSTALL_CMAKEDIR}"
    COMPONENT kreader_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
