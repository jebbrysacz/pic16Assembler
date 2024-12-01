/*

NOTE THAT SECTIONS ARE NOT YET IMPLEMENTED


*/

#include "Section.hh"

std::unordered_map<std::string, Section> Section::sections;

// Default constructor
Section::Section() : name("default") {}

// Constructor with name
Section::Section(const std::string& name) : name(name) {}

// Static method to add a section
void Section::add(const std::string& name) {
    sections.emplace(name, Section(name));
}

// Static method to get a section
const Section& Section::get(const std::string& name) {
    auto it = sections.find(name);
    if (it == sections.end()) {
        throw std::out_of_range("Section not found");
    }
    return it->second;
}

// Accessor for name
std::string Section::get_name() const {
    return name;
}
