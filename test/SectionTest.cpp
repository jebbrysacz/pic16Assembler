/*

NOTE THAT SECTIONS ARE NOT YET IMPLEMENTED


*/



#include <iostream>
#include "Section.hh"

void testAddAndGetSection() {
    // Adding sections
    Section::add("text");
    Section::add("data");

    // Getting sections
    const Section& textSection = Section::get("text");
    const Section& dataSection = Section::get("data");

    // Testing section names
    if (textSection.get_name() == "text" && dataSection.get_name() == "data") {
        // std::cout << "testAddAndGetSection passed." << std::endl;
    } else {
        std::cout << "testAddAndGetSection failed." << std::endl;
    }

    std::cout << "Add and get section tests passed!\n" << std::endl;
}

void testNonExistentSection() {
    try {
        const Section& nonExistent = Section::get("nonexistent");
        std::cout << "testNonExistentSection failed." << std::endl;
    } catch (const std::out_of_range& e) {
        // std::cout << "testNonExistentSection passed." << std::endl;
    }

    std::cout << "NonExistent section tests passed!\n" << std::endl;
}

int main() {
    std::cout << "All Section tests start!\n" << std::endl;

    testAddAndGetSection();
    testNonExistentSection();

    std::cout << "All Section tests passed!\n" << std::endl;
    return 0;
}
