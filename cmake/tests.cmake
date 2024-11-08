include(CTest)
enable_testing()

set(UNIT_TEST_DIR "${CMAKE_SOURCE_DIR}/tests")
file(GLOB_RECURSE TESTS "${UNIT_TEST_DIR}/*.cpp")

foreach(i ${TESTS})
  file(RELATIVE_PATH name ${UNIT_TEST_DIR} ${i})
  cmake_path(REMOVE_EXTENSION name)
  string(REPLACE "/" "_" name ${name})
  set(test_bin "test_${name}")

  add_executable(${test_bin} ${i})
  # Link against the only library we're planing to build
  target_link_libraries(${test_bin} gtest_main "${OurLib}")
  add_test(NAME ${test_bin} COMMAND ${test_bin})
endforeach()
