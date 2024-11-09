#include "slowbpe.h"
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <list>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <ranges>

namespace {

using namespace std;

}  // namespace

namespace slow {

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

namespace v1 {

namespace {

struct DigramData {
  // the given digram number of occ. updated online
  size_t count = 0;
  // this is updated lazily as opposed to above,
  // we also keep the list of occurences sorted
  vector<list<int>::iterator> occurrences{};
};

// (count, digram), may be out-of-sync!
using QueueItem = pair<int, pair<int, int>>;

struct Comparator {
  bool operator()(QueueItem lhs, QueueItem rhs) {
    if (lhs.first == rhs.first) {
      // if the counts are the same, we should do greater to get
      // lexicographically smallest digram on top of the queue
      return lhs.second > rhs.second;
    }
    // in the normal scenario, priority_queue with less is a max queue
    return lhs.first < rhs.first;
  };
};

constexpr int kSentinelToken = numeric_limits<int>::min();

}  // namespace

Result RunBpe(const std::vector<int>& tokens, int firstToken, int num_iters) {
  // 1. Keep up-to-date encoding in a list to erase elements in the middle.
  list<int> encoding(begin(tokens), end(tokens));
  // 2. Use a hash map to track each digram stats.
  boost::unordered_map<std::pair<int, int>, DigramData> digram_data;
  for (auto it = begin(encoding); next(it) != end(encoding); ++it) {
    ++digram_data[pair{*it, *next(it)}].count;
    digram_data[pair{*it, *next(it)}].occurrences.push_back(it);
  }
  // 3. Keep counts in a max queue. This is updated lazily as well.
  priority_queue<QueueItem, vector<QueueItem>, Comparator> q;
  for (const auto& [p, d] : digram_data) {
    q.push(pair{d.count, p});
  }

  Result result;
  for (; num_iters--; ++firstToken) {
    auto selected = pair{kSentinelToken, kSentinelToken};
    // - Select the most common digram, cleanup the queue if needed
    while (q.size()) {
      auto [c, p] = q.top();
      q.pop();
      if (auto it = digram_data.find(p);
          it != end(digram_data) && it->second.count == c) {
        selected = p;
        break;
      }
    }
    if (selected == pair{kSentinelToken, kSentinelToken}) {
      break;
    }
    // - Update the encoding and the map
    // Some existing digram disappear, and new digrams appear (each of them
    // contains the newly minted token). We update the encoding, and the map
    // counts in a loop, but update the queue in the end at once.
    boost::unordered_set<pair<int, int>> changed_digrams;
    for (const auto it : digram_data[selected].occurrences) {
      const auto jt = next(it);
      if (jt == end(encoding) || selected != pair{*it, *jt}) {
        // This can happen as we change the list in this loop. Example: "aaa".
        continue;
      }
      // Now, we have something like (l or r can be none in the corner case):
      // `... l -> selected.first -> selected.second -> r ...`
      if (it != encoding.begin()) {
        const auto l = std::prev(it);

        const auto old_digram = pair{*l, selected.first};
        const auto new_digram = pair{*l, firstToken};
        changed_digrams.insert(old_digram);
        changed_digrams.insert(new_digram);
        --digram_data[old_digram].count;
        ++digram_data[new_digram].count;
        // we don't care when an occurrence disappears (mostly b/c it's annoying
        // to delete it like that), but we should definitely newly created ones.
        digram_data[new_digram].occurrences.push_back(l);
      }
      if (const auto r = next(jt); r != end(encoding) && *r != kSentinelToken) {
        const auto old_digram = pair{selected.second, *r};
        const auto new_digram = pair{firstToken, *r};
        changed_digrams.insert(old_digram);
        changed_digrams.insert(new_digram);
        --digram_data[old_digram].count;
        ++digram_data[new_digram].count;
        digram_data[new_digram].occurrences.push_back(jt);
      }
      // counts should now be updated, update the encoding now
      *it = kSentinelToken;
      encoding.splice(encoding.end(), encoding, it);
      *jt = firstToken;
    }
    // - Update the queue now
    for (auto p : changed_digrams) {
      q.push({digram_data[p].count, p});
    }
    digram_data.erase(selected);
    // - Record our decision to merge
    result.merging.emplace_back(selected.first, selected.second, firstToken);
  }
  for (int x : encoding) {
    if (x == kSentinelToken)
      break;
    result.encoding.push_back(x);
  }
  return result;
}

}  // namespace v1
