# sources
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library("${OurLib}" ${sources})

# including headers --- keep files plainly here
target_include_directories("${OurLib}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
