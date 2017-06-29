//
// Created by alex on 05.12.16.
//

#ifndef LAB2_STRINGPARSER_H
#define LAB2_STRINGPARSER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class StringParser {
private:
    std::vector<std::string> sourceAlphabet;

    void setSourceAlphabet(std::string filename);

    unsigned long getMaxWordLength();

    std::string getFirstLongestValidWord(std::string);

    bool ifValidWord(std::string);

public:
    explicit StringParser(std::string);

    std::vector<std::string> getSourceAlphabet();

    static std::vector<std::string> getLineFromFile(std::string filename);

    std::vector<std::string> parseMessage(std::string);


};


#endif //LAB2_STRINGPARSER_H
