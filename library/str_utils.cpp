#include "str_utils.hh"

#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

// From internet
std::string join_strings(const std::vector<std::string>& vec, const std::string& separator) {
    if (vec.empty()) return "";
    return std::accumulate(std::next(vec.begin()), vec.end(), vec[0],
                           [&separator](const std::string& a, const std::string& b) {
                               return a + separator + b;
                           });
}

// From internet
std::vector<std::string> split_string(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(delimiter, start);
    }
    result.push_back(str.substr(start)); // Add the last segment
    
    return result;
}

std::string trim_left(const std::string& str) {
    std::string result = str;
    result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return result;
}

