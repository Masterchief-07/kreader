include(GenerateExportHeader)

add_library(kreader csv.cpp)

add_library(kreader::kreader ALIAS kreader)

target_link_libraries(kreader PRIVATE myproject_options myproject_warnings)

target_include_directories(kreader ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                                  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(kreader PUBLIC cxx_std_20)

set_target_properties(
  kreader
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)

generate_export_header(kreader EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/include/kreader/kreader_export.hpp)

if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(kreader PUBLIC KREADER_STATIC_DEFINE)
endif()

