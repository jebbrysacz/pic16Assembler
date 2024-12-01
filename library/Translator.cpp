// Translator.cpp
#include "Translator.hh"

// Messaging events
#include "EventEnum.hh"

// Structures
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

// C utils
#include <stdexcept>
#include <cctype>


// Math utils
#include <cmath>
#include <algorithm>

// String utils
#include <string>
#include <string.h>

// Streams
#include <iostream>
#include <fstream>
#include <sstream>


// Initialize maps
std::unordered_map<std::string, std::string> Translator::text_label_hashmap = {};
std::unordered_map<std::string, std::string> Translator::data_label_hashmap = {};
std::unordered_map<std::string, std::string> Translator::const_hashmap = {};

// Map to keep track of expressions
std::unordered_map<std::string, bool> exp_hashmap = {};

// Foreward declarations
std::string evaluate_expression(const std::string &expression, const std::unordered_map<std::string, std::string> &symbol_table);

// Constructor
Translator::Translator(const std::string& inputPath, const std::string& outputPath) : 
    input_file_path(inputPath), 
    output_file_path(outputPath), 
    cur_section(".text"),
    contains_error(false) {}

// Accessors and setters
std::string Translator::get_input_file_path() const {return this->input_file_path;}
std::string Translator::get_output_file_path() const {return this->output_file_path;}

std::string Translator::get_cur_section() const {return this->cur_section;}

EventEnum Translator::get_message() const {return this->message;}

std::string Translator::get_error_message() const {return this->error_message;}

bool Translator::get_contains_error() const {return this->contains_error;}

std::vector<std::shared_ptr<Line>> Translator::get_lines_array() {return this->lines_array;}


void Translator::set_input_file_path(const std::string& new_input_file_path){
    this->input_file_path = new_input_file_path;
    }
void Translator::set_output_file_path(const std::string& new_output_file_path){
    this->output_file_path = new_output_file_path;
}
void Translator::set_cur_section(const std::string& new_section){
    this->cur_section = new_section;
}
void Translator::set_message(EventEnum new_message){
    this->message = new_message;
}
void Translator::set_error_message(const std::string& new_error_message){
    this->error_message = new_error_message;
}
void Translator::set_contains_error(bool new_result){
    this->contains_error = new_result;
}

// Essential translator functions
EventEnum Translator::define_lines(const std::string& file_info) {
    // Make sure file path is valid and open
    std::ifstream file(file_info);
    if (!file.is_open()) {
        // std::cerr << "Error opening file: " << file_info << std::endl;
        this->error_message = "Error opening file: " + file_info + "\n";
        return EventEnum::FILE_NOT_FOUND;
    }

    // Set up temp variables
    std::string lineContent;
    uint64_t lineNumber = 1; 

    // Parse file line by line
    while (std::getline(file, lineContent)) {
        // ".include" is an important pseudo op that must be handled as it is declared
        std::istringstream iss(lineContent);
        std::string word;
        // ISS strips spaces and tabs for easy comparison
        iss >> word;
        if(word == ".include") {
            // Run define_lines recursively if a ".include" appears
            std::string includeFile;
            // Check that the include path parameter is not empty
            iss >> includeFile;
            if(!includeFile.empty()) {
                // Remove quotes if present
                if(includeFile.front() == '"' && includeFile.back() == '"') {
                    includeFile = includeFile.substr(1, includeFile.size() - 2);
                }
                define_lines(includeFile); // Recursive call to include the file
            }
            // MAYBE ADD A CONTINUE OR BREAK HERE
        } 
        // Other urgent speudo ops are the section modifiers TODO
        else if((word.compare(".text")==0) || (word.compare(".data")==0) || (word.compare(".info")==0)) {
            this->cur_section = word;
            // MAYBE ADD A CONTINUE OR BREAK HERE
        }
        // Before initalizing the line, it must not be empty
        else if (!lineContent.empty()) {
            std::shared_ptr<Line> line = std::make_shared<Line>(lineNumber, this->cur_section, lineContent, file_info);
//TODO, SEE IF YOU CAN CONDENSE THIS PART
            // We must also decide if we should put the line in our array IDEALLY COMBINE THESE
            if (!line->no_comments.empty()) {
            this->lines_array.push_back(std::move(line));
// std::cout << "\tpushed that guy into the array" << std::endl;
            }
        }

        // Increment file line number
        lineNumber++;
    }

    return EventEnum::SUCCESS;
}

uint64_t Translator::convert_string_to_uint64(const std::string& str) {
    int base = 10;
    size_t prefix_length = 0;

    // Check for prefixes and set the base accordingly
    if (str.size() > 2 && str[0] == '0') {
        if (str[1] == 'x' || str[1] == 'X') {
            base = 16;
            prefix_length = 2;
        } else if (str[1] == 'b' || str[1] == 'B') {
            base = 2;
            prefix_length = 2;
        } else if (str[1] == 'f' || str[1] == 'F') {
            base = 8;
            prefix_length = 2;
        }
    } else if (str.size() > 1) {
        char suffix = tolower(str.back());
        if (suffix == 'h') {
            base = 16;
            prefix_length = 1;
        } else if (suffix == 'b') {
            base = 2;
            prefix_length = 1;
        } else if (suffix == 'f') {
            base = 8;
            prefix_length = 1;
        }
    }

    // Remove the prefix if any
    std::string number_str = str.substr(prefix_length, str.size() - prefix_length);

    // TODO: maybe make this an line error
    // JUST DONT MAKE IT CRASH THE PROGRAM FOR NOW
    try {
        return std::stoull(number_str, nullptr, base);
    } catch (const std::invalid_argument& e) {
        // this->error_message = "Invalid argument: " + str;
        // throw std::invalid_argument("Invalid argument: " + str);
    } catch (const std::out_of_range& e) {
        // this->error_message = "Out of range: " + str;        
        // throw std::out_of_range("Out of range: " + str);
    }
}



EventEnum Translator::first_pass() {
    // Init address counters to 0
    uint64_t currentProgramAddress = 0;
    uint64_t currentDataAddress = 0;

    // Make sure that section is defined (".text" by default)
    if (this->cur_section.compare("")==0) {
        this->contains_error = true;
        this->error_message = "Section is not defined!";
        return EventEnum::FILE_FORMAT_ERROR;
    }

    // Loop through each line in the lines array
    for (size_t i = 0; i < this->lines_array.size(); ++i) {
        // Define temp vars
        std::shared_ptr<Line> cur_Line = this->lines_array[i];
        std::string line_str = cur_Line->get_raw_line();
        std::shared_ptr<OpCode> cur_OpCode = cur_Line->get_opcode();
        std::string opcode_str = cur_OpCode->get_code_str();
        std::vector<std::shared_ptr<Operand>> cur_Operands = cur_Line->get_operands();
// printf("\tFirst pass line %ld line w no comments: (%s) has %zu operands\n", this->lines_array[i]->get_line_number(), this->lines_array[i]->no_comments.c_str(), cur_Operands.size());

// printf("BEGINING line: %lu; current prog address: %lu\n", cur_Line->get_line_number(), currentProgramAddress);

    //TODO: SEE IF YOU CAN REMOVE THIS?
        // Remove empty or commented out lines from the array
        if (line_str.empty() == true) {
            this->lines_array.erase(this->lines_array.begin() + i);
            i--;
            currentProgramAddress--;
// printf("\t\t\t\tnot supposed to be here\n");
        }
        // Store user defined values into corresponding hashmaps
        // TODO, SEE IF THIS FLAG CAN BE RENAMED TO MAKE MORE SENSE
        else if (cur_Line->get_contains_user_defined())
        {
            // There are three user defined things
            // - constants
            // - labels
            //   - program memory labels
            //   - data memory labels
// printf("\t\t\t\tuser defined ass foo\n");
            // Check for constant declarations
            if (opcode_str.compare(".EQU") == 0
                || opcode_str.compare(".equ") == 0) {

        // Handle constant declarations

                // Define key value pair
                std::string user_key;
                std::string user_value;

            // Handle expressions
                
                // First handle the first operand (key)
                if (cur_Operands[0]->get_is_expression()) {
                    // // Save old operand string
                    // std::string old_name = cur_Operands[0]->get_raw();

                    // Split the expression
                    std::vector<std::string> words = split_string(cur_Operands[0]->get_raw(), ' ');

                    // Substitute expression elements with defined symbol table values
                    for (auto& word : words) {
                        if (const_hashmap.find(word) != const_hashmap.end()) {
                            word = const_hashmap.at(word);
                        }
                    }
                    // Update the operand
                    cur_Operands[0]->set_raw(join_strings(words, " "));

                    // THIS SHOULD NOT BE IN THIS ONE BECAYSE YOU CAN NOT EQU AN EXPRESSION TO SOMETHING
                    // // Keep track of this operand
                    // exp_hashmap.insert({cur_Operands[0]->get_raw(),cur_Operands[0]->get_raw()});
                } 

                // Update the key
                user_key = cur_Operands[0]->get_raw();
                
                // Next handle the second operand (value)
                if (cur_Operands[1]->get_is_expression()) {
                    // Keep track of this operand for later
                    exp_hashmap.insert({cur_Operands[0]->get_raw(),true});

                    // Split the expression
                    std::vector<std::string> words = split_string(cur_Operands[1]->get_raw(), ' ');

                    // Substitute expression elements with defined symbol table values
                    for (auto& word : words) {
                        if (const_hashmap.find(word) != const_hashmap.end()) {
                            word = const_hashmap.at(word);
                        }
                    }
                    // Update the operand
                    cur_Operands[1]->set_raw(join_strings(words, " "));
                }
// printf("\t\tFirst B4 UPDATE final key-value (%s,%s)\n", user_key.c_str(), user_value.c_str());

                // Update the value
                user_value = cur_Operands[1]->get_raw();
                // Check to see if the key's value has already been defined
                if (const_hashmap.find(user_value) != const_hashmap.end()) {
// printf("\t\tFound a match, already defined\n");
                    // If the value is found to be a key in the map, use that key's mapped value
                    user_value = const_hashmap[user_value];
                }

// printf("\t\tFirst pass final key-value (%s,%s)\n", user_key.c_str(), user_value.c_str());

                // Store in hashmap
                const_hashmap.insert(std::make_pair(user_key, user_value));

                // Remove line from array
                this->lines_array.erase(this->lines_array.begin() + i);
                i--;

                // Start handling next line
                continue;
            } 
            // Handle label definitions
            else if (cur_OpCode->get_is_user_defined())
            {   // Only labels have user defined opcodes

                // Handle text section label
                if (cur_Line->get_section().compare(".text") == 0) {
                    // Fetch key value pair
                    std::string user_key = opcode_str.substr(0, cur_OpCode->get_code_str().size()-1);
                    std::string user_value = std::to_string(currentProgramAddress);
                    
                    // Store in hashmap
                    const_hashmap.insert(std::make_pair(user_key, user_value));
                } 
                // Handle data section label
                else if (this->get_lines_array()[i]->get_section().compare(".data") == 0) {
                    // Fetch key value pair
                    std::string user_key = this->get_lines_array()[i]->get_opcode()->get_code_str().substr(0, cur_OpCode->get_code_str().size()-1);
                    std::string user_value = std::to_string(currentDataAddress);

                    // TODO: VALIDATE THAT YOU ARE ONLY STORING A BYTE AND NO MORE
                    // Update data addresses by one byte
                    currentDataAddress++;

                    // Store in hashmap
                    const_hashmap.insert(std::make_pair(user_key, user_value));
                }
                // Remove line from array
                this->lines_array.erase(this->lines_array.begin() + i);
                i--;

                // Handle next line
                continue;
            }
            else {
                // If any operand is a symbol to an expression, make sure that it knows that it is an expression to be parsed later
                for (size_t i = 0; i < cur_Operands.size(); i++) {
                    // Check every operand for expression to see if it is a symbol to an expression
                    if (exp_hashmap.find(cur_Operands[i]->get_raw()) != exp_hashmap.end()) {
                        // Update the operand's expression boolean if a match was found
// printf("WOW THIS WAS ACUTALLY A GOOD FIX\n");
                        cur_Operands[i]->set_is_expression(true);
                    } 
                }
            }
        }
        else if(opcode_str == ".org") {
            // The only code location pseudo op that the PIC16 MCASM supports is .org
            currentProgramAddress = convert_string_to_uint64(cur_Operands[0]->get_raw());
// printf("\tUpdated current prog address to: %lu due to .org\n", currentProgramAddress);
            // Remove line from array
            this->lines_array.erase(this->lines_array.begin() + i);
            i--;

            // Start handling next line
            continue;
            // currentProgramAddress -= 2;

            // Substitute already defined values into expressoins
            // TODO, move this to seconds pass eventually
            // Handle expressions
            // for (size_t i = 0; i < cur_Operands.size(); i++) {
            //     // Check every operand for expression and handle if exists
            //     if (cur_Operands[i]->get_is_expression()) {
            //         // Split the expression
            //         std::vector<std::string> words = split_string(cur_Operands[i]->get_raw(), ' ');
            //         // Substitute expression elements with defined symbol table values
            //         for (auto& word : words) {
            //             if (const_hashmap.find(word) != const_hashmap.end()) {
            //                 word = const_hashmap.at(word);
            //             }
            //         }
            //         // Update the operand
            //         cur_Operands[0]->set_raw(join_strings(words, " "));
            //     } 
            // }
        }

        // Store program address value in line
// printf("\tMID line: %lu; current prog address: %lu\n", cur_Line->get_line_number(), currentProgramAddress);
        cur_Line->set_memory_address(currentProgramAddress);

        // After every instruction, increment the address by two bytes
        currentProgramAddress += 2;
// printf(" END line: %lu; current prog address: %lu\n\n", cur_Line->get_line_number(), currentProgramAddress);
    }    
    
    return EventEnum::SUCCESS;
}


EventEnum Translator::second_pass() {
    // Check to make sure that the output file is valid
    std::ofstream outputFile(this->output_file_path);
    if (!outputFile.is_open()) {
        // std::cerr << "Error opening output file: " << this->output_file_path << std::endl;
        this->error_message = "Error opening output file: " + this->output_file_path + "\n";
        return EventEnum::FILE_NOT_FOUND;
    }

    // The start of hex files should be an extended linear address record
    // The standard format is :02000004AAAACC
    // - : required start of all lines
    // - 02 2 bytes of address data 
    // - 0000 address section, must be zero
    // - 04 denotes the extended linear addresss data
    // - AAAA actual extended linear address
    // - CC checksum
    // For PIC we can use :020000040000FA
    outputFile << ":020000040000FA" << std::endl;    

    // The lines array should be filtered, loop through remaining lines
    for (const auto& line : this->lines_array) {
        // Before translating, operands that are expressions must be resolved
        for (const auto& operand : line->get_operands()) {
            // printf("\"%s\" operand in second pass: |%s| bin: %s\n", line->no_comments.c_str(), operand->get_raw().c_str(), operand->get_binary().c_str());
            if (operand->get_is_expression()) {
                // If an operand was found to be an expression, attempt to evaluate it
                try {
                    // Handle the case where the expression is held by a user defined symbol
                    if (const_hashmap.find(operand->get_raw()) != const_hashmap.end()) {
                        operand->set_raw(const_hashmap.at(operand->get_raw()));
                    }
                    
                    // Set the raw value to what the expression evaluates to in decimal
                    operand->set_raw(evaluate_expression(operand->get_raw(), this->const_hashmap));

                    // Update the operand's binary parameter
                    operand->parseRawToBinary();
                } catch (const std::exception &e) {
                    // If there was an error in evaluating the expression, TODO: Figure out what to do
                    // Print for now (just debugging)
                    // std::cerr << "Error evaluating expression: " << operand->get_raw() << " - " << e.what() << std::endl;
                }
            }
        }

        // Translate instruction
        outputFile << line->to_pichex(const_hashmap) << std::endl;
    }

    // Hex files must end with ":00000001FF" by convention
    // This is called the end of file record
    outputFile << ":00000001FF" << std::endl;
    outputFile.close();
    return EventEnum::SUCCESS;
}

int precedence(char op) {
    // Helper to decide which parts of the expression to evaluate
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

std::string evaluate_expression(const std::string &expression, const std::unordered_map<std::string, std::string> &symbol_table) {
    // Set up stacks for expression tree
    std::stack<int> values;
    std::stack<char> operators;

    // Functional operator handler
    auto apply_operator = [](std::stack<int> &values, char op) {
        int b = values.top(); values.pop();
        int a = values.top(); values.pop();
        switch (op) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/': values.push(a / b); break;
        }
    };

    // Helper function to convert a number string to an integer considering its base
    auto convert_to_decimal = [](const std::string &num_str) -> int {
        if (num_str.size() >= 2 && (num_str[0] == '0')) {
            char prefix = tolower(num_str[1]);
            if (prefix == 'x') {
                return std::stoi(num_str.substr(2), nullptr, 16);
            } else if (prefix == 'b') {
                return std::stoi(num_str.substr(2), nullptr, 2);
            } else if (prefix == 'f') {
                return std::stoi(num_str.substr(2), nullptr, 8);
            }
        } else if (num_str.size() >= 1) {
            char suffix = tolower(num_str.back());
            if (suffix == 'h') {
                return std::stoi(num_str.substr(0, num_str.size() - 1), nullptr, 16);
            } else if (suffix == 'b') {
                return std::stoi(num_str.substr(0, num_str.size() - 1), nullptr, 2);
            } else if (suffix == 'f') {
                return std::stoi(num_str.substr(0, num_str.size() - 1), nullptr, 8);
            }
        }
        return std::stoi(num_str); // Decimal by default
    };

    // Parse the expression tree
    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isspace(ch)) {
            continue;
        } else if (isdigit(ch) || ch == '0') {
            std::string num_str;
            while (i < expression.length() && (isdigit(expression[i]) || isalpha(expression[i]))) {
                num_str += expression[i];
                ++i;
            }
            --i;
            int value = convert_to_decimal(num_str);
            values.push(value);
        } else if (isalpha(ch)) {
            std::string symbol;
            while (i < expression.length() && (isalnum(expression[i]) || expression[i] == '_')) {
                symbol += expression[i];
                ++i;
            }
            --i;
            if (symbol_table.find(symbol) != symbol_table.end()) {
                int value = convert_to_decimal(symbol_table.at(symbol));
                values.push(value);
            } else {
                throw std::runtime_error("Undefined symbol: " + symbol);
            }
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                apply_operator(values, operators.top());
                operators.pop();
            }
            if (!operators.empty()) {
                operators.pop();
            }
        } else if (strchr("+-*/", ch)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                apply_operator(values, operators.top());
                operators.pop();
            }
            operators.push(ch);
        }
    }

    // Evaluate the expression
    while (!operators.empty()) {
        apply_operator(values, operators.top());
        operators.pop();
    }

    return std::to_string(values.top());
}

void Translator::write_output() {
    // Implementation TODO
    // ERROR HANDLINE PROB
}

// EventEnum Translator::handle_message(EventEnum event) {
//     // Implementation TODO
//     this->message = event;
//     return EventEnum::SUCCESS;
// }

void Translator::reset() {
    // this->input_file_path.clear();
    // this->output_file_path.clear();
    this->cur_section = ".text";
    this->message = EventEnum::SUCCESS;
    this->error_message.clear();
    this->contains_error = false;
    this->lines_array.clear();

    this->text_label_hashmap.clear();
    this->data_label_hashmap.clear();
    this->const_hashmap.clear();
}