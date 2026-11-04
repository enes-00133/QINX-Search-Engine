#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "indexer.h"

#include <iostream>

TEST_CASE("reading file into indexing process") {
    // check if the content of a file is read correctly
    CHECK(readFile("testfile.txt") == "test file content");

    // check the correct return value for the case that file couldn't be opened
    CHECK(readFile("fakeFile.txt") == "");
}

TEST_CASE("readFile prints error message on non-existing file") {
    std::stringstream buffer;

    std::streambuf* oldCerr = std::cerr.rdbuf(buffer.rdbuf());

    readFile("nonExistent.txt");

    // we revert the puffer to it's prior state
    std::cerr.rdbuf(oldCerr);

    // check if expected error message
    CHECK(buffer.str().find("Something went wrong") != std::string::npos); // npos (no position).
    // so we check if the string/errormsg exists in the buffer
}

TEST_CASE("parseFile() indexes words correctly") {
    std::unordered_map<std::string, std::list<std::string>> indexMap;
    std::stringstream fakeFile("Test file content");
    std::stringstream fakeFile2("Test this thing");

    parseFile("testFile", fakeFile, indexMap);
    parseFile("testFile2", fakeFile2, indexMap);

    CHECK(indexMap.size() == 5);
    CHECK(indexMap["test"].front() == "testFile");
    CHECK(indexMap["file"].back() == "testFile");
}