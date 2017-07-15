//
// Created by alex on 26.06.17.
//

#ifndef LAB2_READER_H
#define LAB2_READER_H

#include <stdio.h>
#include <string>
#include <fstream>

class Reader {
public:
    static std::string readMessage(std::string filename) {
        std::ifstream f_message;
        f_message.open(filename, std::ios::in);

        std::string message = "";
        getline(f_message, message);

        return message;
    }
};

#endif //LAB2_READER_H
