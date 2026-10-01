// a search engine
// Enes Sen

#include "indexer.h"
#include <fstream>
#include <sstream>

// todo:

// Read files
std::string readFile(std::string fileName)
{
    std::ifstream file(fileName.c_str());

    // check if file is open
    if (!file.is_open())
    {
        std::cerr << "Something went wrong!" << "\n";
        return "";
    }

    std::string line;
    std::cout << "Reading file" << "\n";

    std::stringstream fileContent;
    fileContent << file.rdbuf();

    // close file
    file.close();

    return fileContent.str();
}

void parseFile(const std::string& fileName, std::istream& file, std::unordered_map<std::string, std::list<std::string>>& indexMap)
{
   std::string word;

    // iterate through every word
    while (file >> word)
    {
        // we take the value for this key (word)
        std::list<std::string>& fileList = indexMap[word];

        // check if list is empty or the file already exists for this word in indexMap
        if (fileList.empty() || fileList.back() != fileName) {
            fileList.push_back(fileName);
        }
    }
}

// Indexing (for searching)

// searching