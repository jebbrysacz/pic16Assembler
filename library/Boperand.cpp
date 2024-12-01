#include "Operand.hh"
#include "Boperand.hh"
#include <iostream>

// Constructor
Boperand::Boperand(const std::string &raw) : Operand(raw) {
    // set_size(3);  // Set the size to 3 bits
    // set_binary(raw);  // Set the binary value to match the raw string
}

// Implementation of virtual methods
void Boperand::identifyChild() const {
    std::cout << "This is a Boperand." << std::endl;
}

void Boperand::printValue() const {
    std::cout << "Boperand - Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
}
