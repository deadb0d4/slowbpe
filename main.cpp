#include <filesystem>
#include <slowbpe.h>
#include <utils.h>

using namespace std;

int main() {
  auto benchfile = filesystem::path("benchmarks/static/tinyshakespeare.txt");
  size_t num_tokens = 1024;
  vector<int> tokens = CastStringToInts(ReadText(benchfile));
  if (tokens.size() > num_tokens) {
    tokens.resize(num_tokens);
  }
  v1::RunBpe(tokens, 256, 100);

  return 0;
}
