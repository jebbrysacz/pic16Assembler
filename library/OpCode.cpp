// OpCode.cpp
#include "OpCode.hh"

// Member type defs
#include <string>


// Constructor
OpCode::OpCode(const std::string& code) : 
    code_str(code), size(0), 
    operand_info(""), 
    format(""), binary(""), 
    is_user_defined(false) {}

// Accessors and modifiers
std::string OpCode::get_code_str() {return this->code_str;}
uint64_t OpCode::get_size(){return this->size;}
std::string OpCode::get_operand_info(){return this->operand_info;}
std::string OpCode::get_format(){return this->format;}
std::string OpCode::get_binary(){return this->binary;}
bool OpCode::get_is_user_defined(){return this->is_user_defined;}

void OpCode::set_size(u_int64_t size){this->size = size;}
void OpCode::set_operand_info(std::string operand_info){this->operand_info = operand_info;}
void OpCode::set_format(std::string format){this->format = format;}
void OpCode::set_binary(std::string binary){this->binary = binary;}
void OpCode::set_is_user_defined(bool result){this->is_user_defined = result;}

