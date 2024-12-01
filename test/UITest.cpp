#include "UI.hh"
#include "EventEnum.hh"
#include <cassert>
#include <iostream>
#include <sstream>
#include <functional>

// Function to capture output for testing
std::string captureOutput(std::function<void()> func) {
    std::ostringstream oss;
    std::streambuf* old_cout = std::cout.rdbuf(oss.rdbuf());
    func();
    std::cout.rdbuf(old_cout);
    return oss.str();
}

void test_launchCLI() {
    std::cout << "Starting test_launchCLI" << std::endl;
    UI ui("inputPath", "outputPath");
    std::string output = captureOutput([&]() { ui.launchCLI(); });
    assert(output == "Assembler CLI launched. Please enter a command:\n");
    std::cout << "test_launchCLI passed!" << std::endl;
}

void test_parse_request() {
    std::cout << "Starting test_parse_request" << std::endl;
    UI ui("inputPath", "outputPath");

    std::istringstream input("load file.asm\n");
    std::cin.rdbuf(input.rdbuf()); // Replace cin's buffer with input buffer
    assert(ui.parse_request() == EventEnum::SUCCESS);

    input.str("set_output output.hex\n");
    std::cin.rdbuf(input.rdbuf());
    assert(ui.parse_request() == EventEnum::SUCCESS);

    input.str("translate\n");
    std::cin.rdbuf(input.rdbuf());
    assert(ui.parse_request() == EventEnum::SUCCESS);

    input.str("quit\n");
    std::cin.rdbuf(input.rdbuf());
    assert(ui.parse_request() == EventEnum::SUCCESS);

    input.str("invalid_command\n");
    std::cin.rdbuf(input.rdbuf());
    assert(ui.parse_request() == EventEnum::INVALID_COMMAND);

    std::cout << "test_parse_request passed!" << std::endl;
}

void test_set_response() {
    std::cout << "Starting test_set_response" << std::endl;
    UI ui("inputPath", "outputPath");

    std::string output;

    output = captureOutput([&]() { ui.set_response(EventEnum::SUCCESS); });
    assert(output == "Operation completed successfully.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::INVALID_COMMAND); });
    assert(output == "Invalid command. Please try again.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::INVALID_FILE_PATH); });
    assert(output == "Invalid file path. Please check and try again.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::SYNTAX_ERROR); });
    assert(output == "Syntax error in the input file.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::UNDEFINED_SYMBOL); });
    assert(output == "Undefined symbol encountered.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::FILE_FORMAT_ERROR); });
    assert(output == "File format error detected.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::ERROR_DETECTED); });
    assert(output == "Error detected during processing.\n");

    output = captureOutput([&]() { ui.set_response(EventEnum::OTHER_ERROR); });
    assert(output == "An unspecified error occurred.\n");

    std::cout << "test_set_response passed!" << std::endl;
}

void test_displayHelp() {
    std::cout << "Starting test_displayHelp" << std::endl;
    UI ui("inputPath", "outputPath");
    std::string output = captureOutput([&]() { ui.displayHelp(); });
    assert(output == "Help information: Use 'translate <file path>' to translate an assembly file.\nUse 'help' to display this information.\n");
    std::cout << "test_displayHelp passed!" << std::endl;
}

void test_displayError() {
    std::cout << "Starting test_displayError" << std::endl;
    UI ui("inputPath", "outputPath");
    std::string output = captureOutput([&]() { ui.displayError(); });
    assert(output == "An error occurred. Please try again.\n");
    std::cout << "test_displayError passed!" << std::endl;
}

void test_displaySuccess() {
    std::cout << "Starting test_displaySuccess" << std::endl;
    UI ui("inputPath", "outputPath");
    std::string output = captureOutput([&]() { ui.displaySuccess(); });
    assert(output == "Operation successful.\n");
    std::cout << "test_displaySuccess passed!" << std::endl;
}

int main() {
    std::cout << "UI tests start!\n" << std::endl;

    test_launchCLI();
    test_parse_request();
    test_set_response();
    test_displayHelp();
    test_displayError();
    test_displaySuccess();

    std::cout << "All UI tests passed!\n" << std::endl;
    return 0;
}
