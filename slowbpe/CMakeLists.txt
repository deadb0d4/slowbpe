# sources
file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library("${OurLib}" ${sources})

# use boost
target_include_directories("${OurLib}" PUBLIC ${Boost_INCLUDE_DIRS})

# including headers --- keep files plainly here
target_include_directories("${OurLib}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
