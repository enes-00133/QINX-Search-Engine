#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <sstream>
#include "indexer.h"

int main() {
     // map for indexing
    std::unordered_map<std::string, std::list<std::string>> indexMap;
    std::list<std::string> files;

    // test
    files.insert(files.end(), {"doc1.txt", "doc2.txt", "doc3.txt"});

    // iterate through all files
    for (const std::string file : files) {
        std::string content = readFile(file);

        // only parse if file is not empty
        if (!content.empty()) {
            std::stringstream ss(content);
            
            parseFile(file, ss, indexMap);
        }
    }

    // TEST
    for (const auto& pair : indexMap) {
        std::cout << "Word: " << pair.first << " exists in files:" << "\n";

        for (const std::string& fileName : pair.second) {
            std::cout << "[" << fileName << "] " << "\n";
        }
    }
    // done
    std::cout << "Indexing complete" << std::endl;

    return 0;
}