// a search engine
// Enes Sen

#include "indexer.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

// todo:

/* 
    Takes a filename as parameter. Adds the file to the lists of files.
    Returns an error if file couldn't be opened.
    Returns the content of the file as string.
*/
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

/*
    Parses the file. Maps each word in the file to the corresponding file(s) 
*/
void parseFile(const std::string& fileName, std::istream& fileContent, std::unordered_map<std::string, std::list<std::string>>& indexMap)
{
   std::string word;

    // iterate through every word
    while (fileContent >> word)
    {
        std::string lowerCaseWord = toLowerCase(word);
        std::string cleansedWord = cleanString(lowerCaseWord);

        // we take the value for this key (word)
        std::list<std::string>& fileList = indexMap[cleansedWord];

        // check if list is empty or the file already exists for this word in indexMap
        if (fileList.empty() || fileList.back() != fileName) {
            fileList.push_back(fileName);
        }
    }
}

/*
Turns a string into lowercase
*/
std::string toLowerCase(std::string str) {
    for (char& c : str) {
        c = std::tolower(static_cast<unsigned char>(c));
    }

    return str;
}

/*
Removes certain characters from the string
*/
std::string cleanString(std::string &str) {
    // characters that should be removed from the string
    char toRemove[] {"\",."};

    for (unsigned int i = 0; i < strlen(toRemove); ++i) {
        str.erase(remove(str.begin(), str.end(), toRemove[i]));
    }

    return str;
}