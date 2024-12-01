#include "Operand.hh"
#include "Koperand.hh"
#include <iostream>

// Constructor
Koperand::Koperand(const std::string &raw) : Operand(raw) {
    // set_size(8);  // Set the size to 8 bits
    // set_binary(raw);  // Set the binary value to match the raw string
// printf("\tthis is inside the koperand constuctor where the bool is : %d", this->is_user_defined);
}

void Koperand::identifyChild() const {
    std::cout << "This is a Koperand." << std::endl;
}

void Koperand::printValue() const {
    std::cout << "Koperand - Raw: " << raw << ", Binary: " << binary << ", Size: " << size << std::endl;
}
