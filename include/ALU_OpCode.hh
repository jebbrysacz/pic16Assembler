#ifndef ALU_OpCode_HH
#define ALU_OpCode_HH

#include "OpCode.hh"
#include <string>
#include <unordered_map>
#include <memory>

class ALU_OpCode : public OpCode
{
private:
    

public:
    static std::unordered_map<std::string, std::string> op_format_map;
    static std::unordered_map<std::string, std::string> op_bin_map;
    static std::unordered_map<std::string, std::string> op_operand_map;

    ALU_OpCode(const std::string& opcode);


    void set_size(u_int64_t size) override;
    void set_operand_info(std::string operand_info) override;
    void set_format(std::string format) override;
    void set_binary(std::string binary) override;
    void set_is_user_defined(bool result) override;

    // FOR TESTING
    void print_value() const;



    
    // std::string get_code_str() const override;
    // u_int64_t get_size() const override;
    // std::string get_binary() const override;
    // std::string get_format() const override;
    // bool get_is_pseudo_op() const override;

    // void set_code(std::string code) override;


    // OMG THESE ARE NOT EVEN NEEDED???
    // virtual void set_size(u_int64_t size) override;
    // virtual void set_operand_info(std::string operand_info) override;
    // virtual void set_format(std::string format) override;
    // void set_binary(std::string binary) override;

    // void set_format(std::string format) override;
    // void set_is_pseudo_op(bool result) override;

    // We dont want this for now
    // std::list<std::shared_ptr<Operand>> get_operands() const override;

};

#endif
