cmake_minimum_required(VERSION 3.20)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test files
add_executable(
  cpp_tutorial_tests
  test_core_utils.cpp
  test_tutorial_quest.cpp
)

target_link_libraries(
  cpp_tutorial_tests
  core_lib
  tutorial_lib
  gtest_main
)

target_include_directories(cpp_tutorial_tests PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

# Enable testing
include(GoogleTest)
gtest_discover_tests(cpp_tutorial_tests)
