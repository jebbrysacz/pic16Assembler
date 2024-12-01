// Operand.cpp
#include "Operand.hh"

// String manipulation utils
#include "str_utils.hh"

// Constant manipulation utils
#include <bitset>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <regex>
#include <cmath>

// Structures
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <functional>

// Global Constants
const std::unordered_set<std::string> supported_operations = {"+", "-", "*", "/"};

// Constant handling maps
std::unordered_map<std::string, std::function<std::string(const std::string&)>> Operand::prefix_map = {
    {"0B", Operand::parseBinary}, {"0b", Operand::parseBinary},
    {"0F", Operand::parseOctal}, {"0f", Operand::parseOctal},
    // {"0D", Operand::parseDecimal}, {"0d", Operand::parseDecimal},
    // {"", Operand::parseDecimal}, ALT VERSION OF DECIMAL
    {"0X", Operand::parseHexadecimal}, {"0x", Operand::parseHexadecimal}
};

std::unordered_map<std::string, std::function<std::string(const std::string&)>> Operand::suffix_map = {
    {"B", Operand::parseBinary}, {"b", Operand::parseBinary},
    {"F", Operand::parseOctal}, {"f", Operand::parseOctal},
    // {"D", Operand::parseDecimal}, {"d", Operand::parseDecimal},
    // {"", Operand::parseDecimal}, ALT VERSION OF DECIMAL
    {"H", Operand::parseHexadecimal}, {"h", Operand::parseHexadecimal}
};

// Constructor Helpers
bool contains_expression(const std::string& operand) {
    // Split the operand by spaces
    std::vector<std::string> parts = split_string(operand, ' ');
    
    // Check if any part is an operator
    for (const std::string& part : parts) {
        if (supported_operations.find(part) != supported_operations.end()) {
            return true;
        }
    }
    
    return false;
}

// Constructor
Operand::Operand(const std::string& raw) : raw(raw), binary(""), size(0), is_user_defined(false), is_expression(false) {
    // Before handing individual operands, check for expressions
    if (contains_expression(raw)) {
        this->is_expression = contains_expression(raw);
    } else {
        // TODO maybe you do parse to binary always so maybe move out of the else
        parseRawToBinary();
    }
}

// Util functions
std::string padTo14Bits(const std::string& binaryString) {
    size_t length = binaryString.length();
    if (length >= 14) {
        return binaryString;
    }

    std::string paddedString = std::string(14 - length, '0') + binaryString;
    return paddedString;
}

void Operand::parseRawToBinary() {
    // Return if the string was empty
    if (this->raw.empty()) {
        return;
    }

    // Copy the string into an uppercase testing variable
    std::string tempRaw = raw;
    std::transform(tempRaw.begin(), tempRaw.end(), tempRaw.begin(), ::toupper);

    // Fetch the last character for suffix handling later
    char last_char = tempRaw.back();
    std::string last_char_str(1, last_char); // Convert char to string

    // Process immediate constant values
    if (std::regex_match(tempRaw, std::regex("^[0-9]+$"))) {
        // If the value is only digits, default to parse decimal
        this->binary = parseDecimal(tempRaw);
    }    
    // Now check for constants with supported prefixes
    else if (std::regex_match(tempRaw, std::regex("^0.[0-9,A-F,a-f]+$"))) {
        for (const auto& [prefix, func] : prefix_map) {
            if (tempRaw.find(prefix) == 0) {
                this->binary = func(tempRaw);
            }
        }
    }
    // Suffixes next
    else if (suffix_map.find(last_char_str) != suffix_map.end()
        && std::regex_match(tempRaw, std::regex("^[0-9,A-F,a-f]+.$")) ) {
        for (const auto& [suffix, func] : suffix_map) {
            if (tempRaw.find(suffix) == tempRaw.size()-1) {
                this->binary = func(tempRaw);
            }
        }
    } else {
        // If there was no constant number to turn into binary,
        // then it needs to be a user defined value
        this->is_user_defined = true;
    }

    // Will be 0 if it was not defined
    this->size = binary.length();

    // ADJUST BINARY TO BE 14 BITS
    this->binary = padTo14Bits(this->binary);
}


// TODO maybe refactor or rename or reevaluate these
std::string Operand::parseBinary(const std::string& binaryStr) {
    // Check if the string starts with "0x" and remove it if present
    std::string cleanBinaryStr = binaryStr;
    if (binaryStr.rfind("0b", 0) == 0 || binaryStr.rfind("0B", 0) == 0) {
        cleanBinaryStr = binaryStr.substr(2);
    }
    // Same thing for the suffix
    if (binaryStr.rfind("B", binaryStr.size()-1) == 0 || binaryStr.rfind("b", binaryStr.size()-1) == 0) {
        cleanBinaryStr = binaryStr.substr(0, binaryStr.size()-1);
    }

    return cleanBinaryStr;
}

std::string Operand::parseOctal(const std::string& octalStr) {
    // Check if the string starts with "0x" and remove it if present
    std::string cleanOctalStr = octalStr;
    if (octalStr.rfind("0x", 0) == 0 || octalStr.rfind("0X", 0) == 0) {
        cleanOctalStr = octalStr.substr(2);
    }
    // Same thing for the suffix
    if (octalStr.rfind("H", octalStr.size()-1) == 0 || octalStr.rfind("h", octalStr.size()-1) == 0) {
        cleanOctalStr = octalStr.substr(0, octalStr.size()-1);
    }
    
    // Convert octal string to unsigned long
    std::stringstream ss;
    ss << std::oct << cleanOctalStr;
    unsigned long n;
    ss >> n;

    // Calculate the number of bits needed to represent the number
    int numBits = n > 0 ? static_cast<int>(log2(n)) + 1 : 1;

    // Ensure a minimum bit length, e.g., 14 bits for the specific use case
    const int minBitLength = 14;
    numBits = std::max(numBits, minBitLength);

    // Convert to binary string of appropriate length
    std::string binaryString = std::bitset<64>(n).to_string().substr(64 - numBits);

    return binaryString;
}

std::string Operand::parseDecimal(const std::string& decimalStr) {
    // Convert decimal string to unsigned long
    unsigned long n = std::stoul(decimalStr);

    // Calculate the number of bits needed to represent the number
    int numBits = n > 0 ? static_cast<int>(log2(n)) + 1 : 1;

    // Ensure a minimum bit length, e.g., 14 bits for the specific use case
    const int minBitLength = 14;
    numBits = std::max(numBits, minBitLength);

    // Convert to binary string of appropriate length
    std::string binaryString = std::bitset<64>(n).to_string().substr(64 - numBits);
// printf("\tIn parseDecimal: %s\n", binaryString.c_str());
    return binaryString;
}

std::string Operand::parseHexadecimal(const std::string& hexStr) {

// printf("\tIn parseHex: %s\n", hexStr.c_str());
    // Check if the string starts with "0x" and remove it if present
    std::string cleanHexStr = hexStr;
    if (hexStr.rfind("0x", 0) == 0 || hexStr.rfind("0X", 0) == 0) {
        cleanHexStr = hexStr.substr(2);
    }
    // Same thing for the suffix
    if (hexStr.rfind("H", hexStr.size()-1) == 0 || hexStr.rfind("h", hexStr.size()-1) == 0) {
        cleanHexStr = hexStr.substr(0, hexStr.size()-1);
    }
// printf("\tIn parseHex: %s\n", cleanHexStr.c_str());
    // Convert hexadecimal string to unsigned long
    std::stringstream ss;
    ss << std::hex << cleanHexStr;
    unsigned long n;
    ss >> n;
// printf("\tIn parseHex: %s\n", cleanHexStr.c_str());
    // Calculate the number of bits needed to represent the number
    int numBits = n > 0 ? static_cast<int>(log2(n)) + 1 : 1;

    // Ensure a minimum bit length, e.g., 14 bits for the specific use case
    const int minBitLength = 14;
    numBits = std::max(numBits, minBitLength);

    // Convert to binary string of appropriate length
    std::string binaryString = std::bitset<64>(n).to_string().substr(64 - numBits);
// printf("\tIn parseHex: %s\n", binaryString.c_str());
    return binaryString;
}


uint64_t Operand::get_size(){
    return this->size;
}

std::string& Operand::get_raw(){
    return  this->raw;
}

std::string& Operand::get_binary(){
    return this->binary;
}

bool Operand::get_is_user_defined(){
    return this->is_user_defined;
}

bool Operand::get_is_expression(){
    return this->is_expression;
}

void Operand::set_size(uint64_t size) {
    this->size = size;
}

void Operand::set_raw(const std::string& raw) {
    this->raw = raw;
}

void Operand::set_binary(const std::string& binary) {
    this->binary = binary;
}

void Operand::set_is_user_defined(bool result) {
    this->is_user_defined = result;
}

void Operand::set_is_expression(bool result) {
    this->is_expression = result;
}

// void Operand::printValue() const {
//     std::cout << "BASE OPERAND Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
// }
