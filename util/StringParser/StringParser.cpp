//
// Created by alex on 05.12.16.
//

#include <cstring>
#include "StringParser.h"

StringParser::StringParser(std::string filename) {
    this->setSourceAlphabet(filename);
}

void StringParser::setSourceAlphabet(std::string filename) {
    this->sourceAlphabet = getLineFromFile(filename);
}

std::vector<std::string> StringParser::getLineFromFile(std::string filename) {
    std::vector<std::string> result;

    //open file
    std::ifstream f_alphabet(filename);
    std::istream &str = f_alphabet;
    //get line from file
    std::string line;
    getline(str, line);
    //convert line to stream
    std::stringstream lineStream(line);
    std::string cell;

    while (getline(lineStream, cell, ',')) {
        result.push_back(cell);
    }

    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty()) {
        // If there was a trailing comma then add an empty element.
        result.push_back("");
    }

    return result;
}

std::vector<std::string> StringParser::getSourceAlphabet() {
    return this->sourceAlphabet;
}

/**
 * @returns vector of strings(symbols) in the same order as they appear in message */
std::vector<std::string> StringParser::parseMessage(std::string message) {
    std::vector<std::string> words;

    while (message.size() > 1) {
        std::string firstLongestWord = getFirstLongestValidWord(message);
        words.push_back(firstLongestWord);
        message.erase(0, firstLongestWord.size());
    }

    return words;
}

unsigned long StringParser::getMaxWordLength() {
    unsigned long currentMax = 0;
    for (int i = 0; i < this->sourceAlphabet.size(); ++i) {
        if (currentMax < this->sourceAlphabet[i].size()) {
            currentMax = this->sourceAlphabet[i].size();
        }
    }
    return currentMax;
}

std::string StringParser::getFirstLongestValidWord(std::string string) {
    std::string word;

    unsigned long maxWordLength = getMaxWordLength();
    for (unsigned long i = 0; i < 3; ++i) {
        word = string.substr(0, maxWordLength - i);
        if (ifValidWord(word)) break;
    }

    return word;
}

bool StringParser::ifValidWord(std::string word) {
    bool validation = false;
    for (int i = 0; i < this->sourceAlphabet.size(); ++i) {
        if (word.compare(this->sourceAlphabet[i]) == 0) {
            validation = true;
            break;
        }
    }
    return validation;
}
