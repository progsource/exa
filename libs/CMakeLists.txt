# This project is licensed under the MIT license. For more information see the
# LICENSE file.

cmake_minimum_required(VERSION 2.8)

# ------------------------------------------------------------------------------

set(EXA_CPP_VERSION 14)
add_definitions(-DCPP_VERSION=${EXA_CPP_VERSION})

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# ------------------------------------------------------------------------------

add_library(exa_fmt STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/fmt/src/format.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/fmt/src/posix.cc
)
target_include_directories(exa_fmt PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/fmt/include
)

message(STATUS "added ${White}exa_fmt")

# ------------------------------------------------------------------------------

set(LIBS_INCLUDE_DIRS
# -- fmt -----------------------------------------------------------------------
  ${CMAKE_CURRENT_SOURCE_DIR}/fmt/include
# ------------------------------------------------------------------------------
)

if (EXA_UNIT_TESTS)
  set(LIBS_INCLUDE_DIRS
    ${LIBS_INCLUDE_DIRS}
  # -- googletest / -mock ------------------------------------------------------
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/gtest/googlemock/include
  # ----------------------------------------------------------------------------
  )

  message(STATUS "added ${White}gtest")
endif()

set(LIBS_INCLUDE_DIRS ${LIBS_INCLUDE_DIRS} PARENT_SCOPE)
# ------------------------------------------------------------------------------

set(LIBS_SRC_FILES
PARENT_SCOPE)

set(EXA_LIBS
  exa_fmt
PARENT_SCOPE)
