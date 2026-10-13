#include <sstream>
#include "indexer.h"
#include "cli.h"
#include "file_manager.h"

int main() {

    greetUser();
    const std::filesystem::path root("/Users/enessen/Desktop/TestIterator");
    // test(root);

    /*
    std::string userInput;
    std::cin >> userInput;

    InputCommand cmd = commandHandler(userInput);

    switch (cmd) {
        case VERSION:
        break;

        case EXIT:
        break;

        case HELP:
        break;

        case SEARCH:
        break;
    };
*/
     // map for indexing
    std::unordered_map<std::string, std::list<std::string>> indexMap;
    std::list<std::string> files = findAllFiles(root);

    
    // test
    // files.insert(files.end(), {"doc1.txt", "doc2.txt", "doc3.txt"});

    
    // iterate through all files
    for (const std::string& file : files) {
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
    

    // CLI
    std::string searchQuery;

    std::cout << "========Search for an entry in files========" << "\n";

    while (true) {

        
        // input
        std::cout << ">";
        std::cin >> searchQuery;

        if (searchQuery == "exit") {
            std::cout << "Ending search";
            break;
        }

        std::string lowerCaseWord = toLowerCase(searchQuery);

        auto it = indexMap.find(lowerCaseWord);

        // word found
        if (it != indexMap.end()) {
            
            std::cout << "Entry found in files:" << "\n";
            for (const std::string& fileName : it -> second) {
                std::cout << "[" << fileName << "]" << "\n";
            }
            
        }

        // no entry found
        else {
            std::cout << ">> No files found for this entry: " << "\"" << searchQuery << "\"" << "\n";
        }
    }
    
}