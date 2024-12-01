#include "Operand.hh"
#include "Boperand.hh"
#include "Doperand.hh"
#include "Foperand.hh"
#include "Koperand.hh"

#include <cassert>
#include <iostream>
#include <sstream>
#include <functional>

// Function to capture output for testing
std::string captureOutput(std::function<void()> func) {
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old_cout);
    return oss.str();
}

void test_OperandInitialization() {
    Boperand boperand("0B011");
    boperand.printValue();
    assert(boperand.get_raw() == "0B011");
    assert(boperand.get_size() == 3);
    assert(boperand.get_binary() == "011");

    std::cout << "Operand initialization tests passed!\n" << std::endl;
}

void test_OperandSettersAndGetters() {
    Boperand boperand("B011");
    boperand.set_size(16);
    assert(boperand.get_size() == 16);

    boperand.set_binary("10101010");
    assert(boperand.get_binary() == "10101010");

    boperand.set_raw("B456");
    assert(boperand.get_raw() == "B456");

    std::cout << "Setters and getters tests passed!\n" << std::endl;
}

void test_OperandPrintValue() {
    Boperand boperand("10");
    std::string output = captureOutput([&]() { boperand.printValue(); });
    assert(output == "Boperand - Raw: 10, Binary: 1010, Size: 4\n");

    std::cout << "Print value tests passed!\n" << std::endl;
}

void test_OperandIdentifyChild() {
    Boperand boperand("B123");
    // boperand.identifyChild();
    std::string output = captureOutput([&]() { boperand.identifyChild(); });
    // std::cout << output << std::endl;
    assert(output == "This is a Boperand.\n");

    // std::cout << "WE ABOUT TO MAKE THE DOPERAND" << std::endl;
    Doperand doperand("D456");
    // std::cout << "HE MADE" << std::endl;
    output = captureOutput([&]() { doperand.identifyChild(); });
    // std::cout << output << std::endl;
        // std::cout << "SHIT SHOULD HAVE PRINTED" << std::endl;
    assert(output == "This is a Doperand.\n");

    Foperand foperand("F789");
    output = captureOutput([&]() { foperand.identifyChild(); });
    assert(output == "This is a Foperand.\n");

    Koperand koperand("K101");
    output = captureOutput([&]() { koperand.identifyChild(); });
    assert(output == "This is a Koperand.\n");
    
    std::cout << "Operand identify child tests passed!\n" << std::endl;
}

void test_OperandEquality() {
    // Boperand boperand1("B123");
    // Boperand boperand2("B123");
    // Boperand boperand3("B456");

    // assert(boperand1 == boperand2);
    // assert(boperand1 != boperand3);

    // std::cout << "Operand equality tests passed!\n" << std::endl;
}

void test_OperandCopyConstructor() {
    Boperand boperand1("B123");
    Boperand boperand2 = boperand1;

    assert(boperand2.get_raw() == boperand1.get_raw());
    assert(boperand2.get_size() == boperand1.get_size());
    assert(boperand2.get_binary() == boperand1.get_binary());

    std::cout << "Operand copy constructor tests passed!\n" << std::endl;
}

void test_OperandAssignmentOperator() {
    Boperand boperand1("B123");
    Boperand boperand2("B456");
    boperand2 = boperand1;

    assert(boperand2.get_raw() == boperand1.get_raw());
    assert(boperand2.get_size() == boperand1.get_size());
    assert(boperand2.get_binary() == boperand1.get_binary());

    std::cout << "Operand assignment operator tests passed!\n" << std::endl;
}

int main() {
    std::cout << "Operand tests starting!\n" << std::endl;

    test_OperandInitialization();
    test_OperandSettersAndGetters();
    test_OperandPrintValue();
    test_OperandIdentifyChild();
    test_OperandEquality();
    test_OperandCopyConstructor();
    test_OperandAssignmentOperator();

    std::cout << "All Operand tests passed!\n" << std::endl;
    return 0;
}


// #include "Operand.hh"
// #include "Boperand.hh"
// #include "Doperand.hh"
// #include "Foperand.hh"
// #include "Koperand.hh"

// #include <cassert>
// #include <iostream>
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

// void test_OperandInitialization() {
//     Boperand boperand("0B011");
//     boperand.printValue();
//     assert(boperand.getRaw() == "0B011");
//     assert(boperand.getSize() == 3);
//     assert(boperand.getBinary() == "011");

//     std::cout << "Operand initilaization tests passed!\n" << std::endl;
// }

// void test_OperandSettersAndGetters() {
//     Boperand boperand("B011");
//     boperand.setSize(16);
//     assert(boperand.getSize() == 16);

//     boperand.setBinary("10101010");
//     assert(boperand.getBinary() == "10101010");

//     boperand.setRaw("B456");
//     assert(boperand.getRaw() == "B456");

//     std::cout << "Setters and getters tests passed!\n" << std::endl;
// }

// void test_OperandPrintValue() {
//     Boperand boperand("10");
//     // boperand.printValue();
//     std::string output = captureOutput([&]() { boperand.printValue(); });
//     assert(output == "Boperand - Raw: 10, Binary: 1010, Size: 4\n");

//     std::cout << "Print value tests passed!\n" << std::endl;
// }

// void test_OperandIdentifyChild() {
//     Boperand boperand("B123");
//     std::string output = captureOutput([&]() { boperand.identifyChild(); });
//     std::cout << output << std::endl;
//     assert(output == "This is a Boperand.\n");

//     Doperand doperand("D456");
//     output = captureOutput([&]() { doperand.identifyChild(); });
//     assert(output == "This is a Doperand.\n");

//     Foperand foperand("F789");
//     output = captureOutput([&]() { foperand.identifyChild(); });
//     assert(output == "This is a Foperand.\n");

//     Koperand koperand("K101");
//     output = captureOutput([&]() { koperand.identifyChild(); });
//     assert(output == "This is a Koperand.\n");
    
//     std::cout << "Operand identify child tests passed!\n" << std::endl;
// }

// void test_OperandEquality() {
//     Boperand boperand1("B123");
//     Boperand boperand2("B123");
//     Boperand boperand3("B456");

//     assert(boperand1 == boperand2);
//     assert(boperand1 != boperand3);

//     std::cout << "Operand equality tests passed!\n" << std::endl;
// }

// void test_OperandCopyConstructor() {
//     Boperand boperand1("B123");
//     Boperand boperand2 = boperand1;

//     assert(boperand2.getRaw() == boperand1.getRaw());
//     assert(boperand2.getSize() == boperand1.getSize());
//     assert(boperand2.getBinary() == boperand1.getBinary());

//     std::cout << "Operand copy constructor tests passed!\n" << std::endl;
// }

// void test_OperandAssignmentOperator() {
//     Boperand boperand1("B123");
//     Boperand boperand2("B456");
//     boperand2 = boperand1;

//     assert(boperand2.getRaw() == boperand1.getRaw());
//     assert(boperand2.getSize() == boperand1.getSize());
//     assert(boperand2.getBinary() == boperand1.getBinary());

//     std::cout << "Operand assignment operator tests passed!\n" << std::endl;
// }

// int main() {
//     std::cout << "Operand tests starting!\n" << std::endl;

//     test_OperandInitialization();
//     test_OperandSettersAndGetters();
//     test_OperandPrintValue();
//     test_OperandIdentifyChild();
//     test_OperandEquality();
//     test_OperandCopyConstructor();
//     test_OperandAssignmentOperator();

//     std::cout << "All Operand tests passed!\n" << std::endl;
//     return 0;
// }
