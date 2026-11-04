// a search engine
// 

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

    std::stringstream fileContent;
    fileContent << file.rdbuf();

    // close file
    file.close();

    return fileContent.str();
}

/*
    Parses the file. Maps each word in the file to the corresponding file(s)
*/
void parseFile(const std::string &fileName, std::istream &fileContent, std::unordered_map<std::string, std::list<std::string>> &indexMap)
{
    std::string word;

    // iterate through every word
    while (fileContent >> word)
    {
        // turns word to lowercase and removes characters like ,/ etc
        std::string lowerCaseWord = toLowerCase(word);
        std::string cleansedWord = cleanString(lowerCaseWord);

        // we take the value for this key (word), which is a list of all the files this word is found in
        std::list<std::string> &fileList = indexMap[cleansedWord];

        // check if list is empty or the file already exists for this word in indexMap
        if (fileList.empty() || fileList.back() != fileName)
        {
            fileList.push_back(fileName);
        }
    }
}

std::list<std::string> searchFiles(const std::string &searchQuery, std::unordered_map<std::string, std::list<std::string>> indexMap)
{
    std::stringstream ss(searchQuery);
    std::string word;
    std::list<std::string> resultList;
    bool firstWord = true;

    while (ss >> word)
    {
        std::string lowerCaseWord = toLowerCase(word);
        const auto cleansedWord = cleanString(lowerCaseWord);
        

        // iterator to the point where word is found in the indexmap
        auto it = indexMap.find(cleansedWord);

        // word not found
        if (it == indexMap.end())
        {
            // if a single word is not found, the query is cancelled
            return {};
        }

        // if found, make a list of the list of files
        std::list<std::string> &fileList = it->second;

        // first word in the query
        if (firstWord)
        {
            // the resultList contains only one file which is the first in the query
            resultList = fileList;
            // sort the list
            resultList.sort();
            firstWord = false;
        }
        // not the first word
        else
        {
            // new list that contains all files added to the list until now
            std::list<std::string> sortedCurrent = fileList;
            // we have to sort in order for set_intersection to work
            sortedCurrent.sort();

            // we add all common file names to this list
            std::list<std::string> intersection;

            // iterator through the current list and the result list, common file names are added to the intersection list
            std::set_intersection(
                resultList.begin(), resultList.end(),
                sortedCurrent.begin(), sortedCurrent.end(),
                std::back_inserter(intersection));

            resultList = intersection;
        }

        // if the list is empty, quit loop
        if (resultList.empty())
        {
            break;
        }
    }
    return resultList;
}

void addToFileList(std::list<std::string> &fileList, const std::string fileName)
{
    fileList.push_back(fileName);
}

/*
Turns a string into lowercase
*/
std::string toLowerCase(std::string str)
{
    for (char &c : str)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }

    return str;
}

/*
Removes certain characters from the string
*/
std::string cleanString(std::string &str)
{
    // characters that should be removed from the string
    char toRemove[]{"\",."};

    for (unsigned int i = 0; i < strlen(toRemove); ++i)
    {
        str.erase(remove(str.begin(), str.end(), toRemove[i]));
    }

    return str;
}
