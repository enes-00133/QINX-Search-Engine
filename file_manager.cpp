#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "indexer.h"

void test(const std::filesystem::path& root) {
    std::filesystem::path tsPath(root);

    std::filesystem::directory_entry dir(tsPath);

    if (dir.exists()) {
        std::cout << "This entry exists" << "\n";
    }

    if (dir.is_directory()) {
        std::cout << "This entry is a dir" << std::endl;
    }

    if (dir.is_regular_file()) {
        std::cout << "This entry is a file" << std::endl;
    }
}

std::list<std::string> findAllFiles(const std::filesystem::path& root) {
    // list of files
    std::list<std::string> files;

    // if the given root directory doesn't exist or isn't a directory
    if (!std::filesystem::exists(root) ||
    !std::filesystem::is_directory(root)) {
        // error message
        std::cerr << "Error: Directory doesn't exist or isn't a directory: " <<
        root << "\n";

        // stop process
        return files;
    }
    
    // we iterate starting from the root directory through all directories recursively
    // until the end point is reached
    for (auto entry : std::filesystem::recursive_directory_iterator(root)) {
        // if it's a file
        std::string fileName = entry.path().filename();
        // excluded directory names like DS_Store
        if (entry.is_regular_file() && fileName != ".DS_Store") {
            // add the whole path to the list
            files.push_back(entry.path().string());
        }
    }

    return files; 
}