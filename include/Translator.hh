#ifndef TRANSLATOR_HH
#define TRANSLATOR_HH

#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

#include "Line.hh"
#include "OpCode.hh"
#include "Operand.hh"

#include "Section.hh"
#include "Segment.hh"

#include "EventEnum.hh"
#include "ConstPrefix.hh"

class Translator {
public:
    // Object instance arrays
    std::vector<std::shared_ptr<Line>> lines_array;

    // File paths
    std::string input_file_path;
    std::string output_file_path;

    // Section data members
    std::string cur_section;

    // Response and feedback related members
    EventEnum message;
    std::string error_message;
    bool contains_error;

    // Hashmaps
    static std::unordered_map<std::string, std::string> text_label_hashmap;
    static std::unordered_map<std::string, std::string> data_label_hashmap;
    static std::unordered_map<std::string, std::string> const_hashmap;
    // TODO: SHOULD PROBABLY COMBINE INTO ONE

    // Constructors and destructors
    Translator(const std::string& inputPath, const std::string& outputPath);

    // Accessor and modifier methods
    std::string get_input_file_path() const;
    std::string get_output_file_path() const;
    std::string get_error_file_path() const;
    std::string get_cur_section() const;
    EventEnum get_message() const;
    std::string get_error_message() const;
    bool get_contains_error() const;
    std::vector<std::shared_ptr<Line>> get_lines_array();

    // Setter methods
    void set_input_file_path(const std::string& new_input_file_path);
    void set_output_file_path(const std::string& new_output_file_path);
    void set_error_file_path(const std::string& new_error_file_path);
    void set_cur_section(const std::string& new_section);
    void set_message(EventEnum new_message);
    void set_error_message(const std::string& new_error_message);
    void set_contains_error(bool new_result);

    // Helpers
    uint64_t convert_string_to_uint64(const std::string& str);

    // Essential translation methods
    EventEnum define_lines(const std::string& file_info);
    EventEnum first_pass();
    EventEnum second_pass();

    // IO methods
    void write_output();
    // EventEnum handle_message(EventEnum event);
    
    // Reset
    void reset();

private:
};

#endif
