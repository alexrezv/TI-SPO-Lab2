//
// Created by alex on 04.07.17.
//

#include "CodeRater.h"


CodeRater::CodeRater(std::vector<double> *probabilities, std::vector<std::string> *codeWords) {
    this->probabilities = std::vector<double>(probabilities->begin(), probabilities->end());
    this->codeWords = std::vector<std::string>(codeWords->begin(), codeWords->end());
    this->setEntropy();
    this->setAvgCodewordLength();
    this->setCodeRedundancy();
}

void CodeRater::setEntropy() {
    double sum = 0;
    for (int i = 0; i < this->probabilities.size(); ++i) {
        sum += this->probabilities.at(i) * std::log2(this->probabilities.at(i));
    }
    this->entropy = std::abs(sum);
}

void CodeRater::setAvgCodewordLength() {
    double sum = 0;
    for (int i = 0; i < this->codeWords.size(); ++i) {
        sum += this->codeWords.at(i).length() * this->probabilities.at(i);
    }
    this->avgCodewordLength = sum;
}

void CodeRater::setCodeRedundancy() {
    this->codeRedundancy = this->avgCodewordLength - this->entropy;
}

void CodeRater::checkKraftsInequality() {
    int codeWordsSize = this->codeWords.size();
    unsigned long codewordLength[codeWordsSize];
    for (unsigned long i = 0; i < codeWordsSize; ++i) {
        codewordLength[i] = this->codeWords.at(i).size();
    }

    double kraftsSum = 0;
    for (int j = 0; j < codeWordsSize; ++j) {
        kraftsSum += 1 / std::pow(2, codewordLength[j]);
    }

    if (kraftsSum < 1) {
        std::cout << "│  Code is not optimal:\t" << kraftsSum << " < 1" << std::endl;
    } else if (kraftsSum > 1) {
        std::cout << "│  Code is not optimal:\t" << kraftsSum << " > 1" << std::endl;
    } else {
        std::cout << "│  Code is optimal:\t" << kraftsSum << " = 1" << std::endl;
    }
}

void CodeRater::printCodeRate() {
    std::cout << "│  Entropy is\t" << this->entropy << std::endl;
    std::cout << "│  Average codeword length is\t" << this->avgCodewordLength << std::endl;
    std::cout << "│  Code redundancy is\t" << this->codeRedundancy << std::endl;
    this->checkKraftsInequality();
}