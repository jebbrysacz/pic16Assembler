#include "ConstPrefix.hh"

// Initialize the static member
std::unordered_map<std::string, ConstPrefix> ConstPrefix::const_prefixes;

// Constructor
ConstPrefix::ConstPrefix(const std::string& name) : name(name) {}

// Get the name
std::string ConstPrefix::get_name() const {
    return name;
}

// Get a ConstPrefix by name
const ConstPrefix& ConstPrefix::get(const std::string& name) {
    return const_prefixes.at(name);
}

// Add a new ConstPrefix
void ConstPrefix::add(const std::string& name) {
    const_prefixes.emplace(name, ConstPrefix(name));
}
