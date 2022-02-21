cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/c9461a9b55ba954df0489bab6420eb297bed846b.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(Include)
enable_testing()

#adding my code to tests
add_library(
  result_container
  src/result_container.cpp
)
add_library(
  directory_traverser
  src/directory_traverser.cpp
)
add_library(
  lib_file
  src/file.cpp
)
add_library(
  lib_program
  src/program.cpp
)
add_library(
  threads_pool
  src/threads_pool.cpp
)


#addding test for results container
add_executable(
  result_container_tests
  tests/result_container_tests.cpp
)
target_link_libraries(
  result_container_tests
  gtest_main
  result_container
)

#adding test for threads pool
add_executable(
  threads_pool_tests
  tests/threads_pool_tests.cpp
)
target_link_libraries(
  threads_pool_tests
  gtest_main
  threads_pool
)

#adding test for file
add_executable(
  file_tests
  tests/file_tests.cpp
)
target_link_libraries(
  file_tests
  gtest_main
  lib_file
  result_container
)

#adding test for directory_traverser
add_executable(
  directory_traverser_test
  tests/directory_traverser_tests.cpp
)
target_link_libraries(
  directory_traverser_test
  gtest_main
  directory_traverser
  lib_file
  threads_pool
  result_container
)

include(GoogleTest)
gtest_discover_tests(result_container_tests)