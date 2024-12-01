#include "ALU_OpCode.hh"
#include "Operand.hh"

#include <cstdint>
#include <unordered_map>

std::unordered_map<std::string, std::string> ALU_OpCode::op_format_map = {
    {"MOVWF", "^00...01...$"},  // Move W to f
    {"CLR", "^00...01...$"},    // Clear f (CLRF or CLRW)
    {"CLRF", "00...01...$"},
    {"CLRW", "00...01...$"},
    {"SUBWF", "^00...10...$"},  // Subtract W from f
    {"DECF", "^00...11...$"},   // Decrement f
    {"IORWF", "^00..100...$"},  // Inclusive OR f and W
    {"ANDWF", "^00..101...$"},  // AND f and W
    {"XORWF", "^00..110...$"},  // Exclusive OR f and W
    {"ADDWF", "^00..111...$"},  // Add W to f
    {"MOVF", "^00..000...$"},   // Move f to destination
    {"COMF", "^00..001...$"},   // Complement f
    {"INCF", "^00..010...$"},   // Increment f
    {"DECFSZ", "^00..011...$"}, // Decrement f, skip if zero
    {"RRF", "^00..100...$"},    // Rotate right through carry
    {"RLF", "^00..101...$"},    // Rotate left through carry
    {"SWAPF", "^00..110...$"},  // Swap nibbles of f
    {"INFSZ", "^00..111...$"},  // Increment f, skip if zero
    // Lowercase versions
    {"movwf", "^00...01...$"},{"clr", "^00...01...$"},
    {"clrf", "00...01...$"},{"clrw", "00...01...$"},
    {"subwf", "^00...10...$"},{"decf", "^00...11...$"},
    {"iorwf", "^00..100...$"},{"andwf", "^00..101...$"},
    {"xorwf", "^00..110...$"},{"addwf", "^00..111...$"},
    {"movf", "^00..000...$"},{"comf", "^00..001...$"},
    {"incf", "^00..010...$"},{"decfsz", "^00..011...$"},
    {"rrf", "^00..100...$"},{"rlf", "^00..101...$"},
    {"swapf", "^00..110...$"},{"infsz", "^00..111...$"}

};

/* ONLY NECESARY BITS
std::unordered_map<std::string, std::string> ALU_OpCode::op_bin_map = {
    {"MOVWF", "0000001"},  // Move W to f
    {"CLR",   "000001"},    // Clear f (CLRF or CLRW)
    {"SUBWF", "000010"},  // Subtract W from f
    {"DECF",  "000011"},   // Decrement f
    {"IORWF", "000100"},  // Inclusive OR f and W
    {"ANDWF", "000101"},  // AND f and W
    {"XORWF", "000110"},  // Exclusive OR f and W
    {"ADDWF", "000111"},  // Add W to f
    {"MOVF",  "001000"},   // Move f to destination
    {"COMF",  "001001"},   // Complement f
    {"INCF",  "001010"},   // Increment f
    {"DECFSZ","001011"}, // Decrement f, skip if zero
    {"RRF",   "001100"},    // Rotate right through carry
    {"RLF",   "001101"},    // Rotate left through carry
    {"SWAPF", "001110"},  // Swap nibbles of f
    {"INFSZ", "001111"},  // Increment f, skip if zero
};
*/

// ALL BITS FOR ANDING
std::unordered_map<std::string, std::string> ALU_OpCode::op_bin_map = {
    {"MOVWF", "00000010000000"},  // Move W to f
    {"CLR",   "00000100000000"},    // Clear f (CLRF or CLRW)
    {"CLRF",   "00000100000000"},    // Clear f (CLRF or CLRW)
    {"CLRW",   "00000100000000"},    // Clear f (CLRF or CLRW)
    {"SUBWF", "00001000000000"},  // Subtract W from f
    {"DECF",  "00001100000000"},   // Decrement f
    {"IORWF", "00010000000000"},  // Inclusive OR f and W
    {"ANDWF", "00010100000000"},  // AND f and W
    {"XORWF", "00011000000000"},  // Exclusive OR f and W
    {"ADDWF", "00011100000000"},  // Add W to f
    {"MOVF",  "00100000000000"},   // Move f to destination
    {"COMF",  "00100100000000"},   // Complement f
    {"INCF",  "00101000000000"},   // Increment f
    {"DECFSZ","00101100000000"}, // Decrement f, skip if zero
    {"RRF",   "00110000000000"},    // Rotate right through carry
    {"RLF",   "00110100000000"},    // Rotate left through carry
    {"SWAPF", "00111000000000"},  // Swap nibbles of f
    {"INFSZ", "00111100000000"},  // Increment f, skip if zero
    // Lowercase versions
    {"movwf", "00000010000000"},{"clr", "00000100000000"},
    {"clrf", "00000100000000"},{"clrw", "00000100000000"},
    {"subwf", "00001000000000"},{"decf", "00001100000000"},
    {"iorwf", "00010000000000"},{"andwf", "00010100000000"},
    {"xorwf", "00011000000000"},{"addwf", "00011100000000"},
    {"movf", "00100000000000"},{"comf", "00100100000000"},
    {"incf", "00101000000000"},{"decfsz", "00101100000000"},
    {"rrf", "00110000000000"},{"rlf", "00110100000000"},
    {"swapf", "00111000000000"},{"infsz", "00111100000000"}

};

std::unordered_map<std::string, std::string> ALU_OpCode::op_operand_map = {
    {"MOVWF", "f"},  // Move W to f
    {"CLR", "df"},    // Clear f (CLRF or CLRW)
    {"CLRF", "f"},
    {"CLRW", "w"},
    {"SUBWF", "df"},  // Subtract W from f
    {"DECF", "df"},   // Decrement f
    {"IORWF", "df"},  // Inclusive OR f and W
    {"ANDWF", "df"},  // AND f and W
    {"XORWF", "df"},  // Exclusive OR f and W
    {"ADDWF", "df"},  // Add W to f
    {"MOVF", "df"},   // Move f to destination
    {"COMF", "df"},   // Complement f
    {"INCF", "df"},   // Increment f
    {"DECFSZ", "df"}, // Decrement f, skip if zero
    {"RRF", "df"},    // Rotate right through carry
    {"RLF", "df"},    // Rotate left through carry
    {"SWAPF", "df"},  // Swap nibbles of f
    {"INFSZ", "df"},  // Increment f, skip if zero
    // Lowercase versions
    {"movwf", "f"},{"clr", "df"},{"clrf", "f"},
    {"clrw", "w"},{"subwf", "df"},{"decf", "df"},
    {"iorwf", "df"},{"andwf", "df"},{"xorwf", "df"},
    {"addwf", "df"},{"movf", "df"},{"comf", "df"},
    {"incf", "df"},{"decfsz", "df"},{"rrf", "df"},
    {"rlf", "df"},{"swapf", "df"},{"infsz", "df"}
};

ALU_OpCode::ALU_OpCode(const std::string& opcode) : OpCode(opcode) {
    // Check if this OpCode's format exists
    if (op_format_map.find(opcode) == op_format_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("ALU_OpCode does not have a format");
    } else{
        // If it was valid we should set format
        this->format = op_format_map.at(opcode);        
    }

    // Check if this OpCode's binary exists
    if (op_bin_map.find(opcode) == op_bin_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("ALU_OpCode does not have defined binary");
    } else{
        // If it was valid we should set binary and size
        this->binary = op_bin_map.at(opcode);
        this->size = static_cast<uint64_t>(op_bin_map.at(opcode).size());
                                            
    }

    // Check if this OpCode's operand info exists
    if (op_operand_map.find(opcode) == op_operand_map.end()) {
            // std::cout << "DANG IT " << code << " WAS INVALID " << std::endl;
        throw std::invalid_argument("ALU_OpCode does not have operand info");
    } else{
        // If it was valid we should set operand info
        this->operand_info = op_operand_map.at(opcode);        
    }
}

void ALU_OpCode::set_size(u_int64_t size){
    this->size = size;    
}
void ALU_OpCode::set_operand_info(std::string operand_info){
    this->operand_info = operand_info;
}
void ALU_OpCode::set_format(std::string format){
    this->format = format;
}
void ALU_OpCode::set_binary(std::string binary){
    this->binary = binary;
}
void ALU_OpCode::set_is_user_defined(bool result){
    this->is_user_defined = result;
}


void ALU_OpCode::print_value() const {
    std::cout << "ALU OpCode - Code: " << code_str << ", Binary: " << binary << ", Format: " << format << ", Size: " << size << std::endl;
}

// std::string ALU_OpCode::get_binary() const{
//     return this->binary;
// }

// void ALU_OpCode::set_binary(std::string binary){
//     this->binary = binary;
// }




// std::string ALU_OpCode::get_hex() const {
//     return pichex;
// }

// std::string ALU_OpCode::get_code() const {
//     return code;
// }

// std::list<std::shared_ptr<Operand>> ALU_OpCode::get_operands() const {
//     return operands;
// }

// std::string ALU_OpCode::get_format() const {
//     return format;
// }

// bool ALU_OpCode::is_pseudo_op() const {
//     return false;
// }
