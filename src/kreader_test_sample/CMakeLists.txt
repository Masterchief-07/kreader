add_executable(kreader_exec main.cpp)

target_link_libraries(
  kreader_exec
  PRIVATE myproject::myproject_options
          myproject::myproject_warnings)

target_link_system_libraries(
  kreader_exec
  PRIVATE
          kreader::kreader)

target_include_directories(kreader_exec PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

