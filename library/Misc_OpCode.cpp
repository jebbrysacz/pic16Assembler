#include "Misc_OpCode.hh"
#include <list>
#include <memory>
#include <cstdint>
#include <unordered_map>

std::unordered_map<std::string, std::string> Misc_OpCode::op_format_map = {
    {"NOP", "^0000000"},  // No operation
    {"RETURN", "^0000000"},  // Return from subroutine
    {"RETFIE", "^0000000"},  // Return from interrupt
    {"OPTION", "^0000000"},  // Load OPTION register
    {"SLEEP", "^0000000"},  // Go into standby mode
    {"CLRWDT", "^0000000"},  // Clear Watchdog Timer
    {"TRIS", "^0000000"},   // Load TRIS register
    // Lowercase versions
    {"nop", "^0000000"},{"return", "^0000000"},{"retfie", "^0000000"},
    {"option", "^0000000"},{"sleep", "^0000000"},{"cltwdt", "^0000000"},
    {"tris", "^0000000"}
};

std::unordered_map<std::string, std::string> Misc_OpCode::op_bin_map = {
    {"NOP",    "00000000000000"},  // No operation
    {"RETURN", "00000000001000"},  // Return from subroutine
    {"RETFIE", "00000000001001"},  // Return from interrupt
    {"OPTION", "00000001100010"},  // Load OPTION register
    {"SLEEP",  "00000001100011"},  // Go into standby mode
    {"CLRWDT", "00000001100100"},  // Clear Watchdog Timer
    {"TRIS",   "00000001100100"},    // Load TRIS register
    // Lowercase versions
    {"nop", "00000000000000"},{"return", "00000000001000"},{"retfie", "00000000001001"},
    {"option", "00000001100010"},{"sleep", "00000001100011"},{"cltwdt", "00000001100100"},
    {"tris", "00000001100100"}
};

std::unordered_map<std::string, std::string> Misc_OpCode::op_operand_map = {
    {"NOP", ""},  // No operation
    {"RETURN", ""},  // Return from subroutine
    {"RETFIE", ""},  // Return from interrupt
    {"OPTION", ""},  // Load OPTION register
    {"SLEEP", ""},  // Go into standby mode
    {"CLRWDT", ""},  // Clear Watchdog Timer
    {"TRIS", "f"},    // Load TRIS register
    // Lowercase versions
    {"nop", ""},{"return", ""},{"retfie", ""},
    {"option", ""},{"sleep", ""},{"cltwdt", ""},
    {"tris", "f"}
};

Misc_OpCode::Misc_OpCode(const std::string& opcode) : OpCode(opcode) {

    // Check if this OpCode's format exists
    if (op_format_map.find(opcode) == op_format_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("Misc_OpCode does not have a format");
    } else{
        // If it was valid we should set format
        this->format = op_format_map.at(opcode);        
    }

    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("Misc_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("Misc_OpCode does not have operand info");
    } else{
        // If it was valid we should set operand info
        this->operand_info = op_operand_map.at(opcode);        
    }

    // this->code = opcode;
    // this->operands = operands;
    // auto it = misc_map.find(opcode);
    // if (it != misc_map.end()) {
    //     this->pichex = it->second;
    // } else {
    //     // Handle error or assign a default value
    // }
}

void Misc_OpCode::set_size(u_int64_t size){
    this->size = size;    
}
void Misc_OpCode::set_operand_info(std::string operand_info){
    this->operand_info = operand_info;
}
void Misc_OpCode::set_format(std::string format){
    this->format = format;
}
void Misc_OpCode::set_binary(std::string binary){
    this->binary = binary;
}
void Misc_OpCode::set_is_user_defined(bool result){
    this->is_user_defined = result;
}


void Misc_OpCode::print_value() const {
    std::cout << "Misc OpCode - Code: " << code_str << ", Binary: " << binary << ", Format: " << format << ", Size: " << size << std::endl;
}





// std::string Misc_OpCode::get_hex() const {
//     return pichex;
// }

// std::string Misc_OpCode::get_code() const {
//     return code;
// }

// std::list<std::shared_ptr<Operand>> Misc_OpCode::get_operands() const {
//     return operands;
// }

// std::string Misc_OpCode::get_format() const {
//     return format;
// }

// bool Misc_OpCode::is_pseudo_op() const {
//     return false;
// }
