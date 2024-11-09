################################################################################

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
        GIT_TAG        main)
    FetchContent_MakeAvailable(googletest)
endif()

################################################################################

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_SHALLOW    TRUE
        GIT_PROGRESS   TRUE
        GIT_TAG        v1.6.1)
    set(BENCHMARK_ENABLE_TESTING OFF  CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_LTO     TRUE)
    FetchContent_MakeAvailable(googlebenchmark)
endif()

################################################################################

find_package(Boost 1.86.0 REQUIRED)

################################################################################
