#pragma once
#include <filesystem>
#include <list>
#include <string>

void test(const std::filesystem::path& root);
std::list<std::string> findAllFiles(const std::filesystem::path& root);
