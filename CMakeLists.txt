cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    kreader
    VERSION 0.0.1
    DESCRIPTION "kreader a csv file reader"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    kreader_kreader
    source/csv.cpp
)
add_library(kreader::kreader ALIAS kreader_kreader)

include(GenerateExportHeader)
generate_export_header(
    kreader_kreader
    BASE_NAME kreader
    EXPORT_FILE_NAME export/kreader/kreader_export.hpp
    CUSTOM_CONTENT_FROM_VARIABLE pragma_suppress_c4251
)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(kreader_kreader PUBLIC KREADER_STATIC_DEFINE)
endif()

set_target_properties(
    kreader_kreader PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
    VERSION "${PROJECT_VERSION}"
    SOVERSION "${PROJECT_VERSION_MAJOR}"
    EXPORT_NAME kreader
    OUTPUT_NAME kreader
)

target_include_directories(
    kreader_kreader ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_include_directories(
    kreader_kreader SYSTEM
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
)

target_compile_features(kreader_kreader PUBLIC cxx_std_20)

# find_package(fmt REQUIRED)
# target_link_libraries(kreader_kreader PRIVATE fmt::fmt)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Examples ----

if(PROJECT_IS_TOP_LEVEL)
  option(BUILD_EXAMPLES "Build examples tree." "${kreader_DEVELOPER_MODE}")
  if(BUILD_EXAMPLES)
    add_subdirectory(example)
  endif()
endif()

# ---- Developer mode ----

if(NOT kreader_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of kreader"
  )
endif()

include(cmake/dev-mode.cmake)
