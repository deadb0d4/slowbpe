#include "slowbpe.h"
#include <map>

namespace slow {

namespace {

using namespace std;

}  // namespace

Result RunBpe(const std::vector<int>& tokens, int firstToken, int num_iters) {
  Result result{.encoding = tokens};

  for (; result.encoding.size() > 1 && num_iters--; ++firstToken) {
    map<pair<int, int>, size_t> counter;
    for (size_t i = 0; i + 1 < result.encoding.size(); ++i) {
      ++counter[{result.encoding[i], result.encoding[i + 1]}];
    }
    pair<size_t, pair<int, int>> most_common = {0, {0, 0}};
    for (const auto& [p, c] : counter) {
      if (c > most_common.first) {
        most_common = {c, p};
      }
    }
    result.merging.emplace_back(
        most_common.second.first, most_common.second.second, firstToken);
    vector<int> transformed;
    for (int e : result.encoding) {
      if (transformed.size() &&
          most_common.second == pair{transformed.back(), e}) {
        transformed.back() = firstToken;
      } else {
        transformed.push_back(e);
      }
    }
    result.encoding = std::move(transformed);
  }
  return result;
}

}  // namespace slow
