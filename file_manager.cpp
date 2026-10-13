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
    std::list<std::string> files;

    std::filesystem::path entry(root);

    std::filesystem::directory_entry dir_entry(entry);

    if (!dir_entry.exists()) {
       // änder eihc noch
    }

    // we iterate starting from the root directory through all directories recursively
    // until the end point is reached
    for (auto entry : std::filesystem::recursive_directory_iterator(entry)) {
        // if it's a file
        if (entry.is_regular_file()) {
            // we get the name of the file
            const auto fileName = entry.path().string();
            if (fileName != ".DS_Store") {
            files.push_back(fileName);
            }
        }
    }

    return files; // im gonna change ts
    // für fehler später
    /*
    for (auto entry = std::filesystem::recursive_directory_iterator(entry);
    entry != std::filesystem::recursive_directory_iterator(); ++entry) {
        if ()
    }
    */

}