project("incidental-cxx")

cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# micro library we're going to work on
set(OurLib "slowbpe")

include(FetchContent)
set(FETCHCONTENT_QUIET    FALSE)
set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/cmake-deps")
include(cmake/deps.cmake)

if (ASAN)
  include(cmake/asan.cmake)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  # TODO: add these when needed!
  include(cmake/benchmarks.cmake)
  include(cmake/release.cmake)
elseif (CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(cmake/tests.cmake)
  include(cmake/debug.cmake)
endif()

add_subdirectory("${OurLib}")

include(cmake/main.cmake)
