cmake_minimum_required(VERSION 3.14)

project(kreaderTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(kreader REQUIRED)
  enable_testing()
endif()

find_package(Catch2 REQUIRED)
include(Catch)
# include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)

# ---- Tests ----

add_executable(kreader_test source/kreader_test.cpp)
target_link_libraries(
    kreader_test 
    PRIVATE kreader::kreader
            Catch2::Catch2WithMain
)
target_compile_features(kreader_test PRIVATE cxx_std_20)

catch_discover_tests(kreader_test)

# ---- End-of-file commands ----

add_folders(Test)
