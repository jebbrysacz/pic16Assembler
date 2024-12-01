// Line.hh
#ifndef STR_UTILS_HH
#define STR_UTILS_HH

#include <string>
#include <vector>
#include <numeric>

// Functions
std::string join_strings(const std::vector<std::string>& vec, 
const std::string& separator);

std::vector<std::string> split_string(const std::string& str, char delimiter);

std::string trim_left(const std::string& str);

#endif //STR_UTILS_HH