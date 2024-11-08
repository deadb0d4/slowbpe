set(ASAN_COMPILE_FLAGS
    -fsanitize=address,undefined
    -fno-sanitize-recover=all)
add_compile_options(${ASAN_COMPILE_FLAGS})

set(ASAN_LINK_FLAGS -fsanitize=address,undefined)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ASAN_LINK_FLAGS}")

add_compile_definitions(BOOST_USE_ASAN)
message(STATUS "ASAN is used")
