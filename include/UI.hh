#ifndef UI_HH
#define UI_HH

#include <string>
#include <iostream>
#include "Translator.hh"
#include "EventEnum.hh"

// Define the state_enum
enum class StateEnum {
    START,
    WAITING_FOR_INPUT,
    PROCESSING,
    ERROR,
    DONE
};

class UI {
private:
    std::string inputPath;
    std::string outputPath;

public:
    // UI();
    UI(const std::string& input, const std::string& output);

    void run();
    EventEnum parse_request();
    void set_response(EventEnum response);
    void displayHelp();
    void displayError();
    void displaySuccess();
    void check_error(EventEnum event);
    void launchCLI();
};

#endif
