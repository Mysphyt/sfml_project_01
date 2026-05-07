#include <unordered_map>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cerrno>   // For errno
#include <cstring>  // For strerror

#include "log.h"

std::vector<std::string> SplitString(const std::string &input, char delimiter);
std::unordered_map<std::string, std::vector<std::string>> LoadDataCSV(const std::filesystem::path& filePath);