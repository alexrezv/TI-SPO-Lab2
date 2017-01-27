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

using namespace std;

template <class T>
class Writer{
public:
  static void writeVector(std::vector<T>* vector, std::string filename, string delim = ",") {
    stringstream s;
    string result;
    ofstream file(filename, ios::out);
    copy(vector->begin(),vector->end(), ostream_iterator<T>(s,","));
    result = s.str();
    result.erase(result.size() - 1, 1);
    file << result;
    file.close();
  }
};


#endif //LAB2_UTILWRITER_H