//
// Created by alex on 06.12.16.
//

#ifndef LAB2_UTILWRITER_H
#define LAB2_UTILWRITER_H

#include <vector>
#include <string>
#include <iostream>
#include <ostream>
#include <iterator>
#include <sstream>

template<class T>
class Writer {
public:
    static void writeVector(std::vector<T> *vector, std::string filename, std::string delim) {
        std::stringstream s;
        std::string result;
        std::ofstream file(filename, std::ios::out);
        copy(vector->begin(), vector->end(), std::ostream_iterator<T>(s, delim.c_str()));
        result = s.str();
        if (delim.compare("") != 0) {
            result.erase(result.size() - 1, 1);
        }
        file << result;
        file.close();
    }
};


#endif //LAB2_UTILWRITER_H