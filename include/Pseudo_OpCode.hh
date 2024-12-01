#ifndef PSEUDO_OPCODE_HH
#define PSEUDO_OPCODE_HH

#include "OpCode.hh"
#include "Operand.hh"
#include <list>
#include <memory>
#include <unordered_map>

class Pseudo_OpCode : public OpCode {
public:
    static std::unordered_map<std::string, std::string> op_format_map;
    static std::unordered_map<std::string, std::string> op_bin_map;
    static std::unordered_map<std::string, std::string> op_operand_map;

    Pseudo_OpCode(const std::string& opcode);

    void set_size(u_int64_t size) override;
    void set_operand_info(std::string operand_info) override;
    void set_format(std::string format) override;
    void set_binary(std::string binary) override;
    void set_is_user_defined(bool result) override;

    // FOR TESTING
    void print_value() const;
    
};

#endif
