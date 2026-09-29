// a search engine
// Enes Sen

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <list>

std::string readFile(std::string fileName);
void parseFile(const std::string& fileName, std::istream& file, std::unordered_map<std::string, std::list<std::string>>& indexMap);

int main()
{
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