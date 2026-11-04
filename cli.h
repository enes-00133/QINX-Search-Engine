#pragma once

#include <string>

enum InputCommand {
    HELP,
    EXIT,
    PATH,
    VERSION,
    SEARCH,
    UNDEFINED
};

void greetUser();
InputCommand commandHandler(std::string command);
