#include <unordered_map>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cerrno>   // For errno
#include <cstring>  // For strerror
#include <map>

#include "log.h"

std::vector<std::string> SplitString(const std::string &input, char delimiter);
std::unordered_map<std::string, std::vector<std::string>> LoadDataCSV(const std::filesystem::path& filePath);

class ObjData {
    // Objects with unique "id" values, each new object increments the counter
private:
    static int counter;
    int id;

public:
    ObjData() {
        if (counter == INT32_MAX) {
            throw std::overflow_error("Counter overflow");
        }
        id = ++counter;
    }

    int getId() const {
        return id;
    }

    static int getCounter() {
        return counter;
    }
};