// cli.cpp
// manages the user interface for the CLI
// name

#include "cli.h"
#include "indexer.h"
#include <iostream>
#include <unordered_map>
#include <list>
#include <sstream>
#include <chrono>
#include <thread>

void greetUser() {
    std::cout << 
    "---------------------------\n" <<
    "     QINX FILE MANAGER\n"      <<
    "---------------------------\n" <<
    std::endl;
    
    // delay
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000));

    std::cout <<
    " ________________________" << "\n" << 
    "|        Commands:       |" << "\n" <<
    "| -help -version -search |" << "\n" <<
    "|________________________|" << "\n";

}

InputCommand commandHandler (std::string command) {
    
    InputCommand userCommand;

    std::string commandLower = toLowerCase(command);
    if (commandLower == "exit") {
        userCommand = EXIT;
    }
    else if (commandLower == "help") {
        userCommand = HELP;
    }
    else if (commandLower == "version") {
        userCommand = VERSION;
    }
    else if (commandLower == "search") {
        userCommand = SEARCH;
    }
    else if (commandLower == "path") {
        userCommand = PATH;
    }
    // if its an unknwon command, return undefined
    else {
        userCommand = UNDEFINED;
    }

    return userCommand;
}