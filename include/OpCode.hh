#ifndef __OPCODEHH__
#define __OPCODEHH__

// Member type defs
#include <string>
#include <inttypes.h>
#include <cinttypes>
#include <cstdint>
#include <memory>

// For the children
#include <stdexcept>
#include <iostream>


class OpCode
{
protected:

public:
    // Data members
    std::string code_str;   // OpCode in string representation
    uint64_t size;         // Size of the OpCode portion in bits (This is parts of the 14 bit instruction that are non-negotiables)
    std::string operand_info; // String representation of the OpCode operand_info
    std::string format;     // Regex expression of the OpCode
    std::string binary;     // Binary in string form (CAN BE CHANGED TO BITSET OR BITWISE SOMETHIGN LATER)
    bool is_user_defined;     // Boolean that indicates whether or not the opcode user defined (pseudo op this is only possible if it is a pseudo op)

    // Constructor
    OpCode(const std::string& code);

    // TODO: is this necesary?
    virtual ~OpCode() = default;

    // Accessors and modifiers
    std::string get_code_str();
    uint64_t get_size();
    std::string get_operand_info();
    std::string get_format();
    std::string get_binary();
    bool get_is_user_defined();

    virtual void set_size(uint64_t size);
    virtual void set_operand_info(std::string operand_info);
    virtual void set_format(std::string format);
    virtual void set_binary(std::string binary);
    virtual void set_is_user_defined(bool result);
};

#endif
