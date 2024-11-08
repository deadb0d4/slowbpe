set(BENCH_DIR "${CMAKE_SOURCE_DIR}/benchmarks")

# 1. Download benchmarks files
file(DOWNLOAD
    "https://raw.githubusercontent.com/karpathy/char-rnn/master/data/tinyshakespeare/input.txt"
    "${BENCH_DIR}/static/tinyshakespeare.txt"
)

# 2. Build benchmarks
file(GLOB_RECURSE BENCHS "${BENCH_DIR}/*.cpp")
foreach(i ${BENCHS})
  file(RELATIVE_PATH name ${BENCH_DIR} ${i})
  cmake_path(REMOVE_EXTENSION name)
  string(REPLACE "/" "_" name ${name})
  set(bench_bin "benchmark_${name}")

  add_executable(${bench_bin} ${i})
  target_link_libraries(${bench_bin} benchmark_main "${OurLib}")
endforeach()
