#pragma once

#include <vector>

struct Result {
  std::vector<int> encoding;
  std::vector<std::tuple<int, int, int>> merging;
};

namespace slow {

/// @param tokens initial tokens to encode
/// @param firstToken first allowed token (e.g. 256 means we gonna use it first,
/// and then 257 etc.)
/// @param num_iters number of new tokens to introduce
/// @returns the algorithm result, encoded tokens, and the mapping for the new
/// tokens
Result RunBpe(const std::vector<int>& tokens, int firstToken, int num_iters);

}  // namespace slow
