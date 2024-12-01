#include "Label_OpCode.hh"
#include <list>
#include <memory>
#include <cstdint>
#include <unordered_map>
#include <regex>

// Initialize the static members
std::unordered_map<std::string, std::string> Label_OpCode::op_format_map = {
    {":$", "Label:"},   // Label definition
};

std::unordered_map<std::string, std::string> Label_OpCode::op_bin_map = {
    {"Label:", ""},    // Label definition
};

std::unordered_map<std::string, std::string> Label_OpCode::op_operand_map = {
    {"Label:", "p"},    // Label definition p

};

// Constructor
Label_OpCode::Label_OpCode(const std::string& opcode) : OpCode(opcode) {
    // Check if this OpCode's format exists
    // auto it = op_format_map.begin();
    // std::string first_key = it->first;
    // std::cout << "\tWe got inside LABEL OPCODE DEF" << std::endl;

    std::string first_key = ".*:";
    std::regex pseudo_op_format(first_key);
    if (std::regex_match(opcode, pseudo_op_format)) {
    // std::cout << "\t\tREGEX MATCHED" << std::endl;
        // If it was valid we should set format confirming we have a valid pseudo op
        // this->format = op_format_map.at(first_key);
        this->format = ".*:";
    } else{
    // std::cout << "\t\tREGEX FAILED" << std::endl;
        // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("Label_OpCode does not have a format");
    }

    // Check if this OpCode's binary exists
    // LABEL'S BINARY IS THE VALUE OF PC AND SHOULD BE SET IN FIRST PASS NOT IN CONSTRUCTOR
    this->binary = "";
    this->size = 13;  // Program memory is defined by the device TODO LATER
    // ASSUME 13 BITS FOR NOW
    // if (op_bin_map.find(opcode) == op_bin_map.end()) {
    //         // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
    //     throw std::invalid_argument("Label_OpCode does not have defined binary");
    // } else{
    //     // If it was valid we should set binary and size
    //     this->binary = op_bin_map.at(opcode);
    //     this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    // }

    // Check if this OpCode's operand info exists
    // LABELS DO NOT HAVE ANY OF THIS?
    this->operand_info = "p";
    // if (op_operand_map.find(opcode) == op_operand_map.end()) {
    //         // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
    //     throw std::invalid_argument("Label_OpCode does not have operand info");
    // } else{
    //     // If it was valid we should set operand info
    //     this->operand_info = op_operand_map.at(opcode);        
    // }

    // Labels are always user defined
    this->is_user_defined = true;
        // std::cout << "\t\tDONE DEFING LABEL" << std::endl;

}

void Label_OpCode::set_size(u_int64_t size){
    this->size = size;    
}
void Label_OpCode::set_operand_info(std::string operand_info){
    this->operand_info = operand_info;
}
void Label_OpCode::set_format(std::string format){
    this->format = format;
}
void Label_OpCode::set_binary(std::string binary){
    this->binary = binary;
}
void Label_OpCode::set_is_user_defined(bool result){
    this->is_user_defined = result;
}

void Label_OpCode::print_value() const {
    std::cout << "Label_OpCode - Code: " << code_str << ", Binary: " << binary << ", Format: " << format << ", Size: " << size << std::endl;
}

