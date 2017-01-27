//
// Created by alex on 05.12.16.
//

#include <cstring>
#include "StringParser.h"

StringParser::StringParser(std::string filename) {
    this->setSourceAlphabet(filename);
}

std::vector<std::string> StringParser::parseWords(std::string message) {
    std::cout << message << std::endl;

    std::vector<std::string> words;

    for (int i = 0; i < this->sourceAlphabet.size(); ++i) {
        int j = 0;
        for (; j < message.length(); ++j) {
            std::string s = message.substr(j, this->sourceAlphabet.at(i).size());
            if (s.compare(this->sourceAlphabet.at(i)) == 0) {
                words.push_back(s);
                message.erase(j, this->sourceAlphabet.at(i).size());
                message.insert(j, " ");
            }
        }
    }
    return words;
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
    std::vector<std::string> messageV;
    std::string wordsFromMessage[100] = {};
    std::vector<std::string> words = this->parseWords(message);

    for (int i = 0; i < words.size(); ++i) {
        long posOfWord = message.find(words.at(i), 0);
        wordsFromMessage[posOfWord] = words.at(i);
        for (int j = posOfWord; j < posOfWord+words.at(i).size(); ++j) {
            char dot = '.';
            message.at(j) = dot;
        }
        words.at(i) = "x";
    }

    for (int k = 0; k < 100; ++k) {
        if (wordsFromMessage[k] != "") {
            messageV.push_back(wordsFromMessage[k]);
        }
    }

    return messageV;
}