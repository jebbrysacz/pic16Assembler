#include "W_OpCode.hh"
#include <list>
#include <memory>
#include <cstdint>
#include <unordered_map>

std::unordered_map<std::string, std::string> W_OpCode::op_format_map = {
    {"ADDLW", "^11...."},  // Add literal and W
    {"ANDLW", "^11...."},  // AND literal with W
    {"IORLW", "^11...."},  // Inclusive OR literal with W
    {"MOVLW", "^11...."},  // Move literal to W
    {"RETLW", "^11...."},  // Return with literal in W
    {"SUBLW", "^11...."},  // Subtract W from literal
    {"XORLW", "^11...."},  // Exclusive OR literal with W
    // Lowercase versions
    {"addlw", "^11...."}, {"andlw", "^11...."}, {"iorlw", "^11...."},
    {"movlw", "^11...."}, {"retlw", "^11...."}, {"sublw", "^11...."}, {"xorlw", "^11...."}

};

/* ONLY NECESARY BITS
std::unordered_map<std::string, std::string> W_OpCode::op_bin_map = {
    {"ADDLW", "110000"},  // Add literal and W
    {"ANDLW", "110100"},  // AND literal with W
    {"IORLW", "111000"},  // Inclusive OR literal with W
    {"MOVLW", "111001"},  // Move literal to W
    {"RETLW", "111010"},  // Return with literal in W
    {"SUBLW", "111011"},  // Subtract W from literal
    {"XORLW", "111110"},  // Exclusive OR literal with W
    // Lowercase versions
    {"addlw", "110000"}, {"andlw", "110100"}, {"iorlw", "111000"},
    {"movlw", "111001"}, {"retlw", "111010"}, {"sublw", "111011"}, {"xorlw", "111110"}
}; */


// ALL BITS FOR ANDING
std::unordered_map<std::string, std::string> W_OpCode::op_bin_map = {
    {"MOVLW", "11000000000000"},  // Add literal and W
    {"RETLW", "11010000000000"},  // AND literal with W
    {"IORLW", "11100000000000"},  // Inclusive OR literal with W
    {"ANDLW", "11100100000000"},  // Move literal to W
    {"XORLW", "11101000000000"},  // Return with literal in W
    {"SUBLW", "11110000000000"},  // Subtract W from literal
    {"ADDLW", "11111000000000"},  // Exclusive OR literal with W
    // Lowercase versions
    {"movlw", "11000000000000"}, {"retlw", "11010000000000"}, {"iorlw", "11100000000000"},
    {"andlw", "11100100000000"}, {"xorlw", "11101000000000"}, {"sublw", "11110000000000"}, {"addlw", "11111000000000"}
};

std::unordered_map<std::string, std::string> W_OpCode::op_operand_map = {
    {"ADDLW", "k"},  // Add literal and W
    {"ANDLW", "k"},  // AND literal with W
    {"IORLW", "k"},  // Inclusive OR literal with W
    {"MOVLW", "k"},  // Move literal to W
    {"RETLW", "k"},  // Return with literal in W
    {"SUBLW", "k"},  // Subtract W from literal
    {"XORLW", "k"},  // Exclusive OR literal with W
    // Lowercase versions
    {"addlw", "k"}, {"andlw", "k"}, {"iorlw", "k"},
    {"movlw", "k"}, {"retlw", "k"}, {"sublw", "k"}, {"xorlw", "k"}
};

W_OpCode::W_OpCode(const std::string& opcode) : OpCode(opcode) {
    // Check if this OpCode's format exists
    if (op_format_map.find(opcode) == op_format_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("W_OpCode does not have a format");
    } else{
        // If it was valid we should set format
        this->format = op_format_map.at(opcode);        
    }

    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("W_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("W_OpCode does not have operand info");
    } else{
        // If it was valid we should set operand info
        this->operand_info = op_operand_map.at(opcode);        
    }

    // this->code = opcode;
    // this->operands = operands;
    // auto it = w_map.find(opcode);
    // if (it != w_map.end()) {
    //     this->pichex = it->second;
    // } else {
    //     // Handle error or assign a default value
    // }
}



void W_OpCode::set_size(u_int64_t size){
    this->size = size;    
}
void W_OpCode::set_operand_info(std::string operand_info){
    this->operand_info = operand_info;
}
void W_OpCode::set_format(std::string format){
    this->format = format;
}
void W_OpCode::set_binary(std::string binary){
    this->binary = binary;
}
void W_OpCode::set_is_user_defined(bool result){
    this->is_user_defined = result;
}

void W_OpCode::print_value() const {
    std::cout << "W OpCode - Code: " << code_str << ", Binary: " << binary << ", Format: " << format << ", Size: " << size << std::endl;
}




// std::string W_OpCode::get_hex() const {
//     return pichex;
// }

// std::string W_OpCode::get_code() const {
//     return code;
// }

// std::list<std::shared_ptr<Operand>> W_OpCode::get_operands() const {
//     return operands;
// }

// std::string W_OpCode::get_format() const {
//     return format;
// }

// bool W_OpCode::is_pseudo_op() const {
//     return false;
// }
