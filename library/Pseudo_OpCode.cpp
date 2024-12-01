#include "Pseudo_OpCode.hh"
#include <list>
#include <memory>
#include <cstdint>
#include <unordered_map>
#include <regex>

// Initialize the static members
std::unordered_map<std::string, std::string> Pseudo_OpCode::op_format_map = {
    {"^\\..*", "pseudo"},   // Pseudo code '.' prefix
};

std::unordered_map<std::string, std::string> Pseudo_OpCode::op_bin_map = {
    {".TEXT", ""},     // Start text space
    {".DATA", ""},     // Start data space
    {".INFO", ""},     // Start info space
    {".EQU", ""},      // Constant definition
//    {".INCLUDE", ""},  // Include file
    {".ORG", ""},       // Set program counter reference value
    // Lowercase Versions
    {".text", ""}, {".data", ""}, {".info", ""},
    {".equ", ""}, /*{".include", ""}, */{".org", ""}
};

std::unordered_map<std::string, std::string> Pseudo_OpCode::op_operand_map = {
    {".TEXT", ""},      // Start text space
    {".DATA", ""},      // Start data space
    {".INFO", ""},      // Start info space
    {".EQU", "pp"},     // Constant definition, pp
    // {".INCLUDE", "p"},  // Include file, p
    {".ORG", "p"},      // Set program counter reference value, p
    // Lowercase Versions
    {".text", ""}, {".data", ""}, {".info", ""},
    {".equ", "pp"}, /*{".include", "p"}, */{".org", "p"}
};

// Constructor
Pseudo_OpCode::Pseudo_OpCode(const std::string& opcode) : OpCode(opcode) {
    // Check if this OpCode's format exists
    auto it = op_format_map.begin();
    std::string first_key = it->first;
    // std::cout << "\t\tINSIDE PSEUDO\n" << std::endl;
    // std::string first_key = "^\\..*";
    std::regex pseudo_op_format(first_key);
    // std::cout << "\t\tregex defed\n" << std::endl;
    if (std::regex_match(opcode, pseudo_op_format)) {
        // If it was valid we should set format confirming we have a valid pseudo op
        // std::cout << "\t\twe got a match\n" << std::endl;
        this->format = op_format_map.at(first_key);        
    } else{
        // std::cout << "\t\tno match\n" << std::endl;
        // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("Pseudo_OpCode does not match the format");
    }

    // std::cout << "\t\tCHECKING FOR BIN\n" << std::endl;
    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
        // std::cout << "\t\t\tno bin\n" << std::endl;
        throw std::invalid_argument("Pseudo_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        // std::cout << "\t\t\tbin found\n" << std::endl;
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // std::cout << "\t\tCHECKING FOR OPERANDS\n" << std::endl;
    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
        // std::cout << "\t\t\tops not found\n" << std::endl;
        throw std::invalid_argument("Pseudo_OpCode does not have operand info");
    } else{
        // If it was valid we should set operand info

        // std::cout << "\t\t\tops found\n" << std::endl;
        this->operand_info = op_operand_map.at(opcode);

        // FALSE PSEUDO OPS ARE NEVER USER DEFINED
        // If operand info is non-"" then it is user defined
        // if (this->operand_info.size() != 0) {
        //     this->is_user_defined = true;
        // }
             
    }


}

void Pseudo_OpCode::set_size(u_int64_t size){
    this->size = size;    
}
void Pseudo_OpCode::set_operand_info(std::string operand_info){
    this->operand_info = operand_info;
}
void Pseudo_OpCode::set_format(std::string format){
    this->format = format;
}
void Pseudo_OpCode::set_binary(std::string binary){
    this->binary = binary;
}
void Pseudo_OpCode::set_is_user_defined(bool result){
    this->is_user_defined = result;
}

void Pseudo_OpCode::print_value() const {
    std::cout << "Pseudo_OpCode - Code: " << code_str << ", Binary: " << binary << ", Format: " << format << ", Size: " << size << std::endl;
}







// std::string B_OpCode::get_hex() const {
//     return pichex;
// }

// std::string B_OpCode::get_code() const {
//     return code;
// }

// std::list<std::shared_ptr<Operand>> B_OpCode::get_operands() const {
//     return operands;
// }

// std::string B_OpCode::get_format() const {
//     return format;
// }

// bool B_OpCode::is_pseudo_op() const {
//     return false;
// }
