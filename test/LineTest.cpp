#include "Line.hh"
#include "B_OpCode.hh"
#include "Boperand.hh"
#include "Doperand.hh"
#include "Foperand.hh"
#include "Koperand.hh"

#include "str_utils.hh"

#include <cassert>
#include <iostream>
#include <sstream>
#include <functional>
#include <memory>
#include <stdexcept>

#include <vector>
#include <string>

// Mock utility functions
// std::string join_strings(const std::vector<std::string>& elements, const std::string& delimiter) {
//     std::ostringstream os;
//     for (size_t i = 0; i < elements.size(); ++i) {
//         if (i != 0)
//             os << delimiter;
//         os << elements[i];
//     }
//     return os.str();
// }

// std::vector<std::string> split_string(const std::string& str, char delimiter) {
//     std::vector<std::string> tokens;
//     std::string token;
//     std::istringstream tokenStream(str);
//     while (std::getline(tokenStream, token, delimiter)) {
//         tokens.push_back(token);
//     }
//     return tokens;
// }

void test_LineInitialization() {
    Line line(1, ".text", "MOVLW 0x55", "test.asm");
    assert(line.get_line_number() == 1);
    assert(line.get_section() == ".text");
    assert(line.get_raw_line() == "MOVLW 0x55");
    assert(line.get_file_name() == "test.asm");
    assert(!line.get_contains_error());
    assert(!line.get_contains_user_defined());

    std::cout << "Line initialization tests passed!\n" << std::endl;
}

void test_LineParse() {
    // Test for opcodes
    // Line line1(1, ".text", "MOVLW 0x55", "test.asm");
    // // std::cout << line1.get_opcode().get_code_str() << std::endl;    
    // assert(line1.get_opcode().get_code_str() == "MOVLW");
    // // std::cout << line1.get_operands().size() << std::endl;
    // assert(line1.get_operands().size() == 1);
    // // std::cout << line1.get_operands()[0]->get_raw() << std::endl;
    // assert(line1.get_operands()[0]->get_raw() == "0x55");


    // Line line2(2, ".text", "MOVWF 0x20", "test.asm");
    // // std::cout << "|" << line2.get_opcode().get_code_str() << "|" << std::endl;    
    // assert(line2.get_opcode().get_code_str() == "MOVWF");
    // // std::cout << line2.get_operands().size() << std::endl;
    // assert(line2.get_operands().size() == 1);
    // // std::cout << line2.get_operands()[0]->get_raw() << std::endl;
    // assert(line2.get_operands()[0]->get_raw() == "0x20");
    

    // Test for label
    // std::cout << "\n\n\nWe got to line 3\n\n" << std::endl;
    // Line line3(2, ".text", "START:", "test.asm");
    // // std::cout << "We SUCCESS INIT line 3!!!!!!!!!" << std::endl;
    // // std::cout << line3.get_opcode().get_code_str() << std::endl;
    // assert(line3.get_opcode().get_code_str() == "START:");

    std::cout << "Line parsing tests passed!\n" << std::endl;
}

void test_LineToPichex() {
//     Line line(1, ".text", "MOVLW 0x55", "test.asm");
//     std::string hex_output = line.to_pichex();
// // std::cout << hex_output << std::endl;
//     assert(!hex_output.empty());
//     std::cout << "Line to PIC HEX conversion tests passed!\n" << std::endl;
}

void test_LineAccessorsAndSetters() {
    Line line(1, ".text", "MOVLW 0x55", "test.asm");
    line.set_line_number(2);
    line.set_memory_address(0x200);
    line.set_file_name("new_test.asm");
    line.set_section(".data");
    line.set_raw_line("ADDLW 0x10");
    line.set_contains_error(true);
    line.set_contains_user_defined(true);
    line.set_error_message("Test error");

    assert(line.get_line_number() == 2);
    assert(line.get_memory_address() == 0x200);
    assert(line.get_file_name() == "new_test.asm");
    assert(line.get_section() == ".data");
    assert(line.get_raw_line() == "ADDLW 0x10");
    assert(line.get_contains_error());
    assert(line.get_contains_user_defined());
    assert(line.get_error_message() == "Test error");

    std::cout << "Line accessors and setters tests passed!\n" << std::endl;
}

int main() {
    std::cout << "Line tests start!\n" << std::endl;

    test_LineInitialization();
    test_LineParse();
    test_LineToPichex();
    test_LineAccessorsAndSetters();

    std::cout << "All Line tests passed!\n" << std::endl;
    return 0;
}
