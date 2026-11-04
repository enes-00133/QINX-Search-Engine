#include "indexer.h"
#include "cli.h"
#include "file_manager.h"
#include <sstream>
#include <iostream>
#include <string>
#include <filesystem>

int main() {

    // prints a greeting message for the user
    greetUser();

    // reads the user input
    std::string userInput;
    std::cin >> userInput;

    // const std::filesystem::path root("/Users/enessen/Documents/TestIterator");

    // path of root as a string
    std::string rootPath;
    
    // the input command by user
    InputCommand cmd = commandHandler(userInput);

    // boolean to check if a valid command was entered, otherwise it stays in the loop
    bool commandChosen = false;
    while (!commandChosen) {
        // commandChosen = true;
    switch (cmd) {

        case VERSION:
        break;

        case EXIT:
        break;

        case HELP:
        break;

        case PATH:
        commandChosen = true;
        std::cout << "Welchen Ordner durchsuchen?" << std::endl;
        
        // get pathname as user input
        // std::getline(std::cin, rootPath);
        std::cin >> rootPath;
        break;

        case SEARCH:
        break;

        case UNDEFINED:
        std::cout << "Invalid command" << "\n";
        break;

        default:
        break;
    };

}

    const std::filesystem::path root(rootPath);
    // todo: if dir doesnt exist, go back

    // test(root);

    

    // map for indexing
    std::unordered_map<std::string, std::list<std::string>> indexMap;

    std::cout << "Searching folder..." << std::endl;
    std::list<std::string> files = findAllFiles(root);
    std::cout << "Found " << files.size() << " files." << std::endl;

    
    // test
    // files.insert(files.end(), {"doc1.txt", "doc2.txt", "doc3.txt"});

    
    std::cout << "\n";
    std::cout << "Reading files..." << "\n";


    // iterate through all files
    for (const std::string& file : files) {
        // saves content of current file in string by passing file address to readFile()
        std::string content = readFile(file);

        // only parse if file is not empty
        if (!content.empty()) {
            std::stringstream ss(content);
            
            parseFile(file, ss, indexMap);
        }
    }

    std::cout << "Files read" << "\n";

    // CLI
    std::string searchQuery;

    std::cout << "========Search for an entry in files========" << "\n";

    while (true) {

        
        // input
        std::cout << ">";
        std::getline(std::cin, searchQuery);

        if (searchQuery == "exit") {
            std::cout << "Ending search";
            break;
        }

        
        // list of words searched for
        std::list<std::string> newSearchQuery = searchFiles(searchQuery, indexMap);

        // word(s) found
        if (!newSearchQuery.empty()) {

            std::cout << "Entry found in files:" << "\n";
            for (const std::string &fileName : newSearchQuery) {
                std::cout << "[" << fileName << "]" << "\n";
            }
        }

        // no entry found
        else {
            std::cout << ">> No files found for this entry: " << "\"" << searchQuery << "\"" << "\n";
        }
    }
    
}