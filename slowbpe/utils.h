#pragma once

#include <vector>
#include <string>
#include <filesystem>

std::vector<int> CastStringToInts(const std::string& str);

std::string ReadText(const std::filesystem::path& p);
