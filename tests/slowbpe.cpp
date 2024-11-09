#include <gtest/gtest.h>
#include <slowbpe.h>

namespace {
using namespace std;
}  // namespace

TEST(Slow, Corner1) {
  {
    slow::RunBpe({1}, 2, 100);
  }
  vector<int> tokens = {0, 0, 0};
  {
    auto result = slow::RunBpe(tokens, 4, 1);
    vector<int> expected = {4, 0};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
  {
    auto result = slow::RunBpe(tokens, 4, 2);
    vector<int> expected = {5};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
        {4, 0, 5},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
  {
    auto result = slow::RunBpe(tokens, 4, 100);
    vector<int> expected = {5};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
        {4, 0, 5},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
}

TEST(Slow, Corner2) {
  vector<int> tokens = {1, 2, 0, 2};
  {
    auto result = slow::RunBpe(tokens, 10, 1);
    vector<int> expected = {1, 2, 10};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 2, 10},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
}

TEST(Slow, Smoke1) {
  vector<int> tokens = {0, 0, 0, 1, 3, 0, 0, 0, 1, 0, 2};
  {
    auto result = slow::RunBpe(tokens, 4, 1);
    vector<int> expected = {4, 0, 1, 3, 4, 0, 1, 0, 2};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
  {
    auto result = slow::RunBpe(tokens, 4, 2);
    vector<int> expected = {4, 5, 3, 4, 5, 0, 2};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
        {0, 1, 5},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
  {
    auto result = slow::RunBpe(tokens, 4, 3);
    vector<int> expected = {6, 3, 6, 0, 2};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
        {0, 1, 5},
        {4, 5, 6},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
}

TEST(Slow, Smoke2) {
  vector<int> tokens = {1, 1, 1, 1, 1};
  {
    auto result = slow::RunBpe(tokens, 2, 2);
    vector<int> expected = {2, 3};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {1, 1, 2},
        {2, 1, 3},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
}

TEST(V1, Corner1) {
  {
    v1::RunBpe({1}, 2, 100);
  }
  vector<int> tokens = {0, 0, 0};
  {
    auto result = v1::RunBpe(tokens, 4, 1);
    vector<int> expected = {4, 0};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
  {
    auto result = v1::RunBpe(tokens, 4, 2);
    vector<int> expected = {5};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
        {4, 0, 5},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
  {
    auto result = v1::RunBpe(tokens, 4, 100);
    vector<int> expected = {5};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
        {4, 0, 5},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
}

TEST(V1, Corner2) {
  vector<int> tokens = {1, 2, 0, 2};
  {
    auto result = v1::RunBpe(tokens, 10, 1);
    vector<int> expected = {1, 2, 10};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 2, 10},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
}

TEST(V1, Smoke1) {
  vector<int> tokens = {0, 0, 0, 1, 3, 0, 0, 0, 1, 0, 2};
  {
    auto result = v1::RunBpe(tokens, 4, 1);
    vector<int> expected = {4, 0, 1, 3, 4, 0, 1, 0, 2};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
  {
    auto result = v1::RunBpe(tokens, 4, 2);
    vector<int> expected = {4, 5, 3, 4, 5, 0, 2};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
        {0, 1, 5},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
  {
    auto result = v1::RunBpe(tokens, 4, 3);
    vector<int> expected = {6, 3, 6, 0, 2};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {0, 0, 4},
        {0, 1, 5},
        {4, 5, 6},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
}

TEST(V1, Smoke2) {
  vector<int> tokens = {1, 1, 1, 1, 1};
  {
    auto result = v1::RunBpe(tokens, 2, 2);
    vector<int> expected = {2, 3};
    EXPECT_EQ(result.encoding, expected);

    vector<tuple<int, int, int>> expected_merging = {
        {1, 1, 2},
        {2, 1, 3},
    };
    EXPECT_EQ(result.merging, expected_merging);
  }
}
