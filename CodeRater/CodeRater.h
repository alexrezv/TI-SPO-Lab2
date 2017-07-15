//
// Created by alex on 04.07.17.
//

#ifndef LAB2_CODERATER_H
#define LAB2_CODERATER_H

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "CodeRater.h"
#include "../Shennon_algorithm/Coder.h"

class CodeRater {
private:
    std::vector<double> probabilities;
    std::vector<std::string> codeWords;
    double entropy;
    double avgCodewordLength;
    double codeRedundancy;

    void setEntropy();

    void setAvgCodewordLength();

    void setCodeRedundancy();

    void checkKraftsInequality();

public:
    CodeRater(std::vector<double> *, std::vector<std::string> *);

    void printCodeRate();
};


#endif //LAB2_CODERATER_H
