#include <benchmark/benchmark.h>

#include <utils.h>
#include <filesystem>
#include "slowbpe.h"

namespace {
using namespace std;

auto GetBenchTokens(size_t num_tokens) {
  auto benchfile = std::filesystem::path(__FILE__).parent_path() /
                   "static/tinyshakespeare.txt";
  vector<int> tokens = CastStringToInts(ReadText(benchfile));
  if (tokens.size() > num_tokens) {
    tokens.resize(num_tokens);
  }
  return tokens;
}

}  // namespace

static void BM_Slow(benchmark::State& state) {
  const auto& tokens = GetBenchTokens(state.range(0));
  for (auto _ : state) {
    slow::RunBpe(tokens, 256, state.range(1));
  }
}

BENCHMARK(BM_Slow)           //
    ->Args({1 << 10, 100})   //
    ->Args({1 << 12, 100})   //
    ->Args({1 << 10, 1000})  //
    ->Args({1 << 12, 1000})  //
    ;

static void BM_v1(benchmark::State& state) {
  const auto& tokens = GetBenchTokens(state.range(0));
  for (auto _ : state) {
    v1::RunBpe(tokens, 256, state.range(1));
  }
}

BENCHMARK(BM_v1)             //
    ->Args({1 << 10, 100})   //
    ->Args({1 << 12, 100})   //
    ->Args({1 << 10, 1000})  //
    ->Args({1 << 12, 1000})  //
    ->Args({1 << 20, 100})   //
    ->Args({1 << 20, 1000})  //
    ->Args({1 << 20, 5000})  // For v1, it's probably too much already
    ;
