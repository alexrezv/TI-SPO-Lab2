//
// Created by alex on 11.11.16.
//

#ifndef LAB2_DECODER_H
#define LAB2_DECODER_H

#include <vector>
#include <string>

class Decoder {
private:
    std::vector<std::string> codeAlphabet;
    std::vector<std::string> sourceAlphabet;
    std::vector<std::string> decryptedMessage;
public:
    Decoder(std::vector<std::string>, std::vector<std::string>);

    std::string decodeMessage(std::string);

    long compareToCode(std::string);
};


#endif //LAB2_DECODER_H
