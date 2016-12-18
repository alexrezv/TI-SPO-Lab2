//
// Created by alex on 11.11.16.
//

#include "Decoder.h"
#include <iostream>

Decoder::Decoder(std::vector<std::string> sourceAlphabet, std::vector<std::string> codeAlphabet) {
    this->codeAlphabet = codeAlphabet;
    this->sourceAlphabet = sourceAlphabet;
}

std::string Decoder::decodeMessage(std::string message) {
    std::string decoded;
    while (!message.empty()) {
        std::string symbol;
        for (unsigned int i = 0; i < message.length(); ++i) {
            symbol += message.at(i);
            if (compareToCode(symbol) != -1) {
                this->decryptedMessage.push_back(this->sourceAlphabet.at(compareToCode(symbol)));
                message.erase(0, i + 1);
                break;
            }
        }
        decoded += this->decryptedMessage.back();
    }
    return decoded;
}

int Decoder::compareToCode(std::string symbol) {
    for (int i = 0; i < this->codeAlphabet.size(); ++i) {
        if (symbol.compare(this->codeAlphabet.at(i)) == 0) {
            return i;
        }
    }
    return -1;
}