#include "CTRL_OpCode.hh"
#include <list>
#include <memory>
#include <cstdint>
#include <unordered_map>

std::unordered_map<std::string, std::string> CTRL_OpCode::op_format_map = {
    {"CALL", "^10."},   // Call subroutine
    {"GOTO", "^10."},   // Go to address
    // Lowercase versions
    {"call", "^10."},{"goto", "^10."}
};

std::unordered_map<std::string, std::string> CTRL_OpCode::op_bin_map = {
    {"CALL", "10000000000000"},   // Call subroutine
    {"GOTO", "10100000000000"},   // Go to address
    // Lowercase versions
    {"call", "10000000000000"},{"goto", "10100000000000"}
};

std::unordered_map<std::string, std::string> CTRL_OpCode::op_operand_map = {
    {"CALL", "k"},   // Call subroutine
    {"GOTO", "k"},   // Go to address
    // Lowercase versions
    {"call", "k"},{"goto", "k"}
};

CTRL_OpCode::CTRL_OpCode(const std::string& opcode) : OpCode(opcode) {

    // Check if this OpCode's format exists
    if (op_format_map.find(opcode) == op_format_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("CTRL_OpCode does not have a format");
    } else{
        // If it was valid we should set format
        this->format = op_format_map.at(opcode);        
    }

    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("CTRL_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("CTRL_OpCode does not have operand info");
    } else{
        // If it was valid we should set operand info
        this->operand_info = op_operand_map.at(opcode);        
    }

    // this->code = opcode;
    // this->operands = operands;
    // auto it = ctrl_map.find(opcode);
    // if (it != ctrl_map.end()) {
    //     this->pichex = it->second;
    // } else {
    //     // Handle error or assign a default value
    // }
}


void CTRL_OpCode::set_size(u_int64_t size){
    this->size = size;    
}
void CTRL_OpCode::set_operand_info(std::string operand_info){
    this->operand_info = operand_info;
}
void CTRL_OpCode::set_format(std::string format){
    this->format = format;
}
void CTRL_OpCode::set_binary(std::string binary){
    this->binary = binary;
}
void CTRL_OpCode::set_is_user_defined(bool result){
    this->is_user_defined = result;
}

void CTRL_OpCode::print_value() const {
    std::cout << "CTRL OpCode - Code: " << code_str << ", Binary: " << binary << ", Format: " << format << ", Size: " << size << std::endl;
}





// std::string CTRL_OpCode::get_hex() const {
//     return pichex;
// }

// std::string CTRL_OpCode::get_code() const {
//     return code;
// }

// std::list<std::shared_ptr<Operand>> CTRL_OpCode::get_operands() const {
//     return operands;
// }

// std::string CTRL_OpCode::get_format() const {
//     return format;
// }

// bool CTRL_OpCode::is_pseudo_op() const {
//     return false;
// }
