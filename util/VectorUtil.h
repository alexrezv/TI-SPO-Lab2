//
// Created by alex on 06.12.16.
//

#ifndef LAB2_UTILVECTOR_H
#define LAB2_UTILVECTOR_H

#include <vector>
#include <string>
#include <iostream>

template<class T>
class VectorUtil {
public:
    static void swapElements(std::vector<T> *vector, int firstElementIndex, int secondElementIndex) {
        vector->insert(vector->begin() + firstElementIndex, vector->at(secondElementIndex));
        vector->insert(vector->begin() + secondElementIndex + 1, vector->at(firstElementIndex + 1));
        vector->erase(vector->begin() + firstElementIndex + 1);
        vector->erase(vector->begin() + secondElementIndex + 1);
    }

    static void printVector(std::vector<T> *vector, std::string delim) {
        for (int i = 0; i < vector->size(); ++i) {
            std::cout << vector->at(i);
            if (i != vector->size() - 1) {
                std::cout << delim;
            }
        }
        std::cout << std::endl;
    }

};


#endif //LAB2_UTILVECTOR_H