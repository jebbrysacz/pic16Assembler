#include <iostream>
#include "OpCode.hh"
#include "ALU_OpCode.hh"
#include <cassert>
#include <sstream>
#include <functional>

// Function to capture output for testing
std::string capture_output(std::function<void()> func) {
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old_cout);
    return oss.str();
}

void test_opcode_initialization() {
    ALU_OpCode alu_opcode("MOVWF");

    assert(alu_opcode.get_code_str() == "MOVWF");
    assert(alu_opcode.get_binary() == "0000001");
    assert(alu_opcode.get_format() == "^00...01...$");
    assert(alu_opcode.get_size() == 7);
    assert(alu_opcode.get_operand_info() == "f");

    std::cout << "OpCode initialization tests passed!\n" << std::endl;
}

void test_opcode_print_value() {
    ALU_OpCode alu_opcode("MOVWF");

    std::string output = capture_output([&]() { alu_opcode.print_value(); });
    std::string expected_output = "ALU OpCode - Code: MOVWF, Binary: 0000001, Format: ^00...01...$, Size: 7\n";
    assert(output == expected_output);

    std::cout << "OpCode print value tests passed!\n" << std::endl;
}

int main() {
    std::cout << "OpCode tests start!\n" << std::endl;

    test_opcode_initialization();
    test_opcode_print_value();

    std::cout << "All OpCode tests passed!\n" << std::endl;
    return 0;
}




// #include <iostream>
// #include <list>
// #include "OpCode.hh"
// #include "ALU_OpCode.hh"
// #include "Operand.hh"
// #include "Boperand.hh"

// #include <assert.h>
// #include <cassert>

// #include <sstream>
// #include <functional>

// // Function to capture output for testing
// std::string captureOutput(std::function<void()> func) {
//     std::ostringstream oss;
//     std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
//     func();
//     std::cout.rdbuf(old_cout);
//     return oss.str();
// }

// void test_OpCodeInitialization() {
//     std::list<std::shared_ptr<Operand>> operands;
//     operands.push_back(std::make_shared<Boperand>("operand_raw"));

//     ALU_OpCode alu_opcode("MOVWF", operands);

//     assert(alu_opcode.get_code() == "MOVWF");
//     assert(alu_opcode.get_hex() == "00001");
//     assert(alu_opcode.get_format() == "00");
//     assert(!alu_opcode.is_pseudo_op());

//     std::cout << "OpCode initialization tests passed!\n" << std::endl;
// }

// void test_OpCodeOperands() {
//     std::list<std::shared_ptr<Operand>> operands;
//     operands.push_back(std::make_shared<Boperand>("operand_raw"));

//     ALU_OpCode alu_opcode("MOVWF", operands);

//     auto op_list = alu_opcode.get_operands();
//     assert(op_list.size() == 1);

//     auto operand = op_list.front();
//     assert(operand->getRaw() == "operand_raw");

//     std::cout << "OpCode operands tests passed!\n" << std::endl;
// }

// void test_OpCodePrintValue() {
//     std::list<std::shared_ptr<Operand>> operands;
//     operands.push_back(std::make_shared<Boperand>("operand_raw"));

//     ALU_OpCode alu_opcode("MOVWF", operands);

//     std::string output = captureOutput([&]() { alu_opcode.get_operands().front()->printValue(); });
//     std::string expected_output = "Boperand - Raw: operand_raw, Binary: , Size: 0\n";
//     assert(output == expected_output);

//     std::cout << "OpCode print value tests passed!\n" << std::endl;
// }

// void test_OpCodeMultipleOperands() {
//     std::list<std::shared_ptr<Operand>> operands;
//     operands.push_back(std::make_shared<Boperand>("operand1_raw"));
//     operands.push_back(std::make_shared<Boperand>("operand2_raw"));

//     ALU_OpCode alu_opcode("MOVWF", operands);

//     auto op_list = alu_opcode.get_operands();
//     assert(op_list.size() == 2);

//     auto first_operand = op_list.front();
//     assert(first_operand->getRaw() == "operand1_raw");

//     auto second_operand = op_list.back();
//     assert(second_operand->getRaw() == "operand2_raw");

//     std::cout << "OpCode multiple operands tests passed!\n" << std::endl;
// }

// int main() {
//     std::cout << "OpCode tests start!\n" << std::endl;

//     test_OpCodeInitialization();
//     test_OpCodeOperands();
//     test_OpCodePrintValue();
//     test_OpCodeMultipleOperands();

//     std::cout << "All OpCode tests passed!\n" << std::endl;
//     return 0;
// }





// // void test_op_code_default_constructor() {
// //     OpCode opcode = OpCode();
// //     std::cout << "Testing default constructor:" << std::endl;

// //     std::cout << "Hex: " << (opcode.get_hex().empty() ? "Pass" : "Fail") << std::endl;
// //     std::cout << "Code: " << (opcode.get_code().empty() ? "Pass" : "Fail") << std::endl;
// //     std::cout << "Operands: " << (opcode.get_operands().empty() ? "Pass" : "Fail") << std::endl;
// //     std::cout << "Format: " << (opcode.get_format().empty() ? "Pass" : "Fail") << std::endl;
    
// //     std::cout << "Default Constructor test passed!" << std::endl;
// // }

// // void test_opcode_constructor() {
// //     list<Operand> ops;
// //     ops.push_back(Operand("CLR"));
// //     OpCode opcode = ALU_OpCode("CLR", ops);
    
// //     std::cout << "Testing constructor:" << std::endl;
    
// //     std::cout << "Hex: " << opcode.get_hex() << std::endl;
// //     assert(opcode.get_hex().compare("CLR"));
// //     std::cout << "Code: " << opcode.get_code() << std::endl;
// //     assert(opcode.get_code().compare("0001"));
// //     std::cout << "Operands: " << (opcode.get_operands().empty() ? "Pass" : "Fail") << std::endl;
// //     assert(opcode.get_code().compare("CLR"));
// //     std::cout << "Format: " << (opcode.get_format().empty() ? "Pass" : "Fail") << std::endl;
// //     assert(opcode.get_code().compare("CLR"));



// //     // assert(opcode.operands == );
// //     // Boperand boperand(&opcode, "raw_data");
// //     // std::cout << "Testing Boperand constructor:" << std::endl;
// //     // std::cout << "Size: " << (boperand.getSize() == 3 ? "Pass" : "Fail") << std::endl;
// //     // std::cout << "Raw: " << (boperand.getRaw() == "raw_data" ? "Pass" : "Fail") << std::endl;
// //     // std::cout << "Binary: " << (boperand.getBinary() == "binary_value" ? "Pass" : "Fail") << std::endl;
// //     printf("Constructor test passed! \n");
// // }

// // void run_all_tests() {
// //     test_op_code_default_constructor();
// //     test_opcode_constructor();
// // }

// // int main() {
// //     run_all_tests();
// //     return 0;
// // }
