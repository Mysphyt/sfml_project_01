#include "data.h"

std::vector<std::string> SplitString(const std::string &input, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        if (!item.empty()) { // Skip empty tokens if needed
            tokens.push_back(item);
        }
    }
    return tokens;
}

#include <cerrno>   // For errno
#include <cstring>  // For strerror

std::unordered_map<std::string, std::vector<std::string>> LoadDataCSV(const std::filesystem::path& filePath)
{
    std::unordered_map<std::string, std::vector<std::string>> result;
    std::ifstream file(filePath);

    if (!file.is_open()) { 
        std::cerr << "Failed to open: " << std::filesystem::absolute(filePath) << std::endl;
        return result;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
        if (line.empty())
            continue;

        const size_t colonPos = line.find(':');
        if (colonPos == std::string::npos)
            continue; // Skip malformed lines

        std::string key   = line.substr(0, colonPos);
        std::string value = line.substr(colonPos + 1);

        if (!key.empty())
            result[key].push_back(value);
    }

    return result;
}
