#include "Operand.hh"
#include "Doperand.hh"
#include <iostream>

// Constructor
Doperand::Doperand(const std::string &raw) : Operand(raw) {
    // set_size(1);  // Set the size to 1 bit
    // set_binary(raw);  // Set the binary value to match the raw string
}

void Doperand::identifyChild() const {
    std::cout << "This is a Doperand." << std::endl;
}

void Doperand::printValue() const {
    std::cout << "Doperand - Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
}
