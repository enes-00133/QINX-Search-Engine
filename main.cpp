// a search engine
// Enes Sen

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void readFile();
void parseFile();

int dal = 5;

int main() {
    std::cout << "Test init" << "\n";

    // readFile();
    parseFile();

    std::cout << dal;
    return 0;
}

// todo:

// Read files
void readFile() {
    // read file
    std::ifstream myFile ("doc1.txt");

    // check if file is open
    if (!myFile.is_open()) {
        std::cout << "Something went wrong!" << "\n";
        return;
    }

    std::string line;
    std::cout << "Reading file" << "\n";

    while(std::getline(myFile, line)) {
        std::cerr << line << "\n";
    }

    // close file
    myFile.close();

}

void parseFile() {
    std::fstream file("doc2.txt");

    std::string line;

    std::stringstream ss;
    ss << file.rdbuf();

    std::string buffer = ss.str();

    std::cout << buffer << std::endl;



}

// Indexing (for searching)

// searching