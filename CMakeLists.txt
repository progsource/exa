# This project is licensed under the MIT license. For more information see the
# LICENSE file.

cmake_minimum_required(VERSION 2.8)

project(exa)

enable_testing()

# ------------------------------------------------------------------------------

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(colorize)

# ------------------------------------------------------------------------------

message(STATUS "${BoldGreen}----------------------------------------")
message(STATUS "${BoldGreen}-       configuring build for exa      -")
message(STATUS "${BoldGreen}----------------------------------------")

# ------------------------------------------------------------------------------

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  message(STATUS "exa is top-level project")
  set(IS_TOP_LEVEL_PROJECT true)
else()
  message(STATUS "exa was called from other project with add_subdirectory()")
  set(IS_TOP_LEVEL_PROJECT false)
endif()

# ------------------------------------------------------------------------------

# this should only be set to true, if you want to run the tests
if (NOT DEFINED EXA_UNIT_TESTS)
  if (${IS_TOP_LEVEL_PROJECT})
    set(EXA_UNIT_TESTS true)
  else()
    message(STATUS "exa tests are disabled")
    set(EXA_UNIT_TESTS false)
  endif()
endif()

# set the following to true, if you want the tests to output the errors to cerr
if (NOT DEFINED EXA_DEBUG_TESTS)
  set(EXA_DEBUG_TESTS false)
endif()

# ------------------------------------------------------------------------------

if (EXA_UNIT_TESTS)
  add_definitions(-DUNIT_TESTS)
  message(STATUS "with ${BoldGreen}UNIT_TESTS${ColorReset}${Green} defined")
endif()

if (EXA_DEBUG_TESTS)
  add_definitions(-DUNIT_TESTS_DEBUG)
  message(STATUS "${ColorReset}${Yellow}with ${BoldYellow}UNIT_TESTS_DEBUG${ColorReset}${Yellow} defined")
endif()

# ------------------------------------------------------------------------------

set(EXA_CPP_VERSION 14)
add_definitions(-DCPP_VERSION=${EXA_CPP_VERSION})

# ------------------------------------------------------------------------------

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# ------------------------------------------------------------------------------

set(EXA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
file(GLOB_RECURSE EXA_SRC_FILES ${PROJECT_SOURCE_DIR}/src/exa/*.cpp)
file(GLOB_RECURSE EXA_TESTS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp)

# ------------------------------------------------------------------------------

set(
  CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -g -std=c++${EXA_CPP_VERSION} -Wall -Wpedantic -Wextra -Wno-ignored-qualifiers -fno-rtti -fno-exceptions -fsanitize=address -fno-omit-frame-pointer"
)

# ------------------------------------------------------------------------------

if (UNIX AND NOT APPLE)
  execute_process(COMMAND ${CMAKE_CXX_COMPILER}
    -fuse-ld=gold -Wl,--version
    ERROR_QUIET OUTPUT_VARIABLE ld_version
  )

  if ("${ld_version}" MATCHES "GNU gold")
    message(STATUS "Found Gold linker, use faster linker")
    set(CMAKE_EXE_LINKER_FLAGS
      "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold"
    )
    set(CMAKE_SHARED_LINKER_FLAGS
      "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold "
    )
  endif()
endif()

# ------------------------------------------------------------------------------

message(STATUS "${BoldGreen}------- configuring libraries for exa")

if (EXA_UNIT_TESTS)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/gtest/googlemock)
endif()

add_subdirectory(libs)

message(STATUS "${BoldGreen}------- configuring libraries done for exa")

# ------------------------------------------------------------------------------

set(EXA_INCLUDE_DIRS
  ${LIBS_INCLUDE_DIRS}
  ${EXA_INCLUDE_DIR}
)

if (NOT ${IS_TOP_LEVEL_PROJECT})
  set(EXA_INCLUDE_DIRS ${EXA_INCLUDE_DIRS} PARENT_SCOPE)
endif()

# ------------------------------------------------------------------------------

add_library(exa STATIC ${EXA_SRC_FILES} ${LIBS_SRC_FILES})
target_include_directories(exa PRIVATE
  ${EXA_INCLUDE_DIRS}
)
target_link_libraries(exa
  ${EXA_LIBS}
)

# ------------------------------------------------------------------------------

if (EXA_UNIT_TESTS)
  add_executable(
    ExaTests
      ${EXA_TESTS_FILES}
  )
  target_include_directories(ExaTests PRIVATE
    ${EXA_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/tests
  )
  target_link_libraries(ExaTests gmock_main exa)
  add_test(ExaTests ${CMAKE_CURRENT_SOURCE_DIR}/build/ExaTests)
endif()
