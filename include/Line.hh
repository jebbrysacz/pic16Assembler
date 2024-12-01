// Line.hh
#ifndef LINE_HH
#define LINE_HH

// Custom line components
#include "OpCode.hh"
#include "Operand.hh"

// Math utils
#include <inttypes.h>
#include <cinttypes>

// Structures
#include <unordered_map>
#include <vector>
#include <memory>

// String utils
#include "str_utils.hh"
#include <string>

class Line {
private:

public:
    // Data members
    uint64_t line_number;     // Line number in source file
    uint64_t memory_address;  // Memory address (either data or program memory)

    std::string file_name;  // Name of source file

    std::string section;    // Name of section

    std::string raw_line;   // Raw line info
    std::string no_comments;   // Comment filtered line info

    std::shared_ptr<OpCode> opcode;      // OpCode in the line 
    std::vector<std::shared_ptr<Operand>> operands; // List of  pointers to Operands

    bool contains_user_defined;

    // TODO: See if you can remove this
    static std::unordered_map<std::string, std::string> op_type_map;   // This is for knowing which child class constructor to call

    bool contains_error;    // Boolean that represents if the line contains an error
    std::string error_message;  // Error message in case the line's error needs to be identified

    // Constructor
    // Lines should be initalized by the Translator class. 
    // The Translator instance should be able to provide all these parameters.
    Line(uint64_t line_number, const std::string& section,
     const std::string& line, const std::string& f_name);

    // Constructor helper functions
    std::string remove_comments(const std::string &line);
    std::vector<std::string> parse_line(std::string &line);
    void parse_opcode(std::vector<std::string> &elements);
    void parse_operands(std::vector<std::string> &elements, std::string operand_info);

    // to_pichex should return the pichex output of the line to be printed to the output file
    std::string to_pichex(std::unordered_map<std::string, std::string>) const;

    // Accessors
    uint64_t get_line_number(); //const;
    uint64_t get_memory_address(); //const;
    std::string& get_file_name(); //const;
    std::string& get_section(); //const;
    std::string& get_raw_line(); //const;
    std::shared_ptr<OpCode>& get_opcode(); //const;
    std::vector<std::shared_ptr<Operand>>& get_operands(); //const;
    bool get_contains_user_defined(); //const;
    bool get_contains_error(); //const;
    std::string& get_error_message(); //const;

    // Setters
    void set_line_number(uint64_t line);
    void set_memory_address(uint64_t address);
    void set_file_name(std::string name);
    void set_section(std::string section);
    void set_raw_line(std::string line);
    void set_contains_error(bool result);
    void set_contains_user_defined(bool result);
    void set_error_message(std::string message);


};

#endif // LINE_HH
