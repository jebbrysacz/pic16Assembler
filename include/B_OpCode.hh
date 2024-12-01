#ifndef B_OPCODE_HH
#define B_OPCODE_HH

#include "OpCode.hh"
#include "Operand.hh"
#include <list>
#include <memory>
#include <unordered_map>

class B_OpCode : public OpCode {
public:
    static std::unordered_map<std::string, std::string> op_format_map;
    static std::unordered_map<std::string, std::string> op_bin_map;
    static std::unordered_map<std::string, std::string> op_operand_map;

    B_OpCode(const std::string& opcode);

    void set_size(u_int64_t size) override;
    void set_operand_info(std::string operand_info) override;
    void set_format(std::string format) override;
    void set_binary(std::string binary) override;
    void set_is_user_defined(bool result) override;

    // FOR TESTING
    void print_value() const;




//     B_OpCode(const std::string& opcode, const std::list<std::shared_ptr<Operand>>& operands);
//     std::string get_hex() const override;
//     std::string get_code() const override;
//     std::list<std::shared_ptr<Operand>> get_operands() const override;
//     std::string get_format() const override;
//     bool is_pseudo_op() const override;

// private:
//     std::map<std::string, std::string> b_map = {
//         {"BCF", "00"}, {"BSF", "01"},
// 		{"BTFSC", "10"}, {"BTFSS", "11"}
//     };
};

#endif

