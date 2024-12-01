#include "Operand.hh"
#include "Foperand.hh"
#include <iostream>

// Constructor
Foperand::Foperand(const std::string &raw) : Operand(raw) {
    // set_size(7);  // Set the size to 7 bits
    // set_binary(raw);  // Set the binary value to match the raw string
}

void Foperand::identifyChild() const {
    std::cout << "This is a Foperand." << std::endl;
}

void Foperand::printValue() const {
    std::cout << "Foperand - Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
}
