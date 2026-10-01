#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <istream>

std::string readFile(std::string fileName);
void parseFile(const std::string& fileName, std::istream& file, std::unordered_map<std::string, std::list<std::string>>& indexMap);