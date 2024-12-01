/*

NOTE THAT SECTIONS ARE NOT YET IMPLEMENTED


*/


#ifndef SECTION_HH
#define SECTION_HH

#include <string>
#include <unordered_map>
#include <stdexcept>

class Section {

public:
    // Constructors
    Section();
    Section(const std::string& name);

    // Static methods to manage sections
    static void add(const std::string& name);
    static const Section& get(const std::string& name);

    // Accessor for name
    std::string get_name() const;

private:
    std::string name;
    static std::unordered_map<std::string, Section> sections;

};

#endif // SECTION_HH
