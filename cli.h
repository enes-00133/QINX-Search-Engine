#pragma once

#include <string>

enum InputCommand {
    HELP,
    EXIT,
    VERSION,
    SEARCH
};

void greetUser();
InputCommand commandHandler(std::string command);
