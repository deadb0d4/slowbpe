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
