#include "UI.hh"
#include <iostream>
#include <cstdio>

// UI::UI() {}

UI::UI(const std::string& input, const std::string& output)
    : inputPath(input), outputPath(output) {}

void UI::run() {
    Translator translator(inputPath, outputPath);
    // Implementation of the run method
}

EventEnum UI::parse_request() {
    std::string command;
    std::cin >> command;
    if (command == "invalid_command") {
        return EventEnum::INVALID_COMMAND;
    } else if (command == "load") {
        std::cin >> inputPath;
        return EventEnum::SUCCESS;
    } else if (command == "set_output") {
        std::cin >> outputPath;
        return EventEnum::SUCCESS;
    } else if (command == "translate") {
        return EventEnum::SUCCESS;
    } else if (command == "quit") {
        return EventEnum::SUCCESS;
    } else {
        return EventEnum::INVALID_COMMAND;
    }
}

void UI::set_response(EventEnum response) {
    switch (response) {
    case EventEnum::SUCCESS:
        std::cout << "Operation completed successfully.\n";
        break;
    case EventEnum::INVALID_COMMAND:
        std::cout << "Invalid command. Please try again.\n";
        break;
    case EventEnum::INVALID_FILE_PATH:
        std::cout << "Invalid file path. Please check and try again.\n";
        break;
    case EventEnum::SYNTAX_ERROR:
        std::cout << "Syntax error in the input file.\n";
        break;
    case EventEnum::UNDEFINED_SYMBOL:
        std::cout << "Undefined symbol encountered.\n";
        break;
    case EventEnum::FILE_FORMAT_ERROR:
        std::cout << "File format error detected.\n";
        break;
    case EventEnum::ERROR_DETECTED:
        std::cout << "Error detected during processing.\n";
        break;
    case EventEnum::FILE_ERROR:
        std::cout << "File error encountered.\n";
        break;
    case EventEnum::FILE_NOT_FOUND:
        std::cout << "File not found.\n";
        break;
    case EventEnum::OTHER_ERROR:
        std::cout << "An unspecified error occurred.\n";
        break;
    }
}

void UI::displayHelp() {
    std::cout << "Help information: Use 'translate <file path>' to translate an assembly file.\nUse 'help' to display this information.\n";
}

void UI::displayError() {
    std::cout << "An error occurred. Please try again.\n";
}

void UI::displaySuccess() {
    std::cout << "Operation successful.\n";
}

void UI::check_error(EventEnum /*event*/) {
    std::printf("Please see output file %s for more details. \n", outputPath.c_str());
}

void UI::launchCLI() {
    std::cout << "Assembler CLI launched. Please enter a command:\n";
}
