#include "utils.h"

#include <fstream>

std::vector<int> CastStringToInts(const std::string& str) {
  std::vector<int> result(str.size());
  for (size_t i = 0; i < str.size(); ++i) {
    result[i] = (unsigned char)str[i];
  }
  return result;
}

std::string ReadText(const std::filesystem::path& p) {
  std::ifstream file(p);
  return {std::istreambuf_iterator(file), std::istreambuf_iterator<char>()};
}
