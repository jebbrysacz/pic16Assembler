#include "Operand.hh"
#include "Poperand.hh"
#include <iostream>

// Constructor
Poperand::Poperand(const std::string &raw) : Operand(raw) {
    // set_size(3);  // Set the size to 3 bits
    // set_binary(raw);  // Set the binary value to match the raw string
    
    // Pseudo operands are always user defined?
    // set_is_user_defined(true);
}

// Implementation of virtual methods
void Poperand::identifyChild() const {
    std::cout << "This is a Poperand." << std::endl;
}

void Poperand::printValue() const {
    std::cout << "Poperand - Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
}
