//
// Created by alex on 11.11.16.
//

#include "Coder.h"

Coder::Coder(std::string aFilename, std::string pFilename) {
    this->setSourceAlphabet(aFilename);
    this->setP(pFilename);
    //VectorUtil<float>::printVector(&this->p, " , ");
    //VectorUtil<std::string>::printVector(&this->sourceAlphabet, " , ");

    this->sortAlphabetAndP();
    //std::cout << "-----------------------------------------------------------" << std::endl;
    //VectorUtil<float>::printVector(&this->p, " , ");
    //VectorUtil<std::string>::printVector(&this->sourceAlphabet, " , ");

    this->setQ();
    //std::cout << "------------------ Q is ---------------------" << std::endl;
    //VectorUtil<float>::printVector(&this->q, " , ");

    this->setL();
    //std::cout << "------------------ L is ---------------------" << std::endl;
    //VectorUtil<float>::printVector(&this->l, " , ");

    this->setCode();
    //std::cout << "------------------ Code is ---------------------" << std::endl;
    //VectorUtil<std::string>::printVector(&this->code, " , ");

}

void Coder::setSourceAlphabet(std::string filename) {
    this->sourceAlphabet = StringParser::getLineFromFile(filename);
}

std::vector<std::string> Coder::getSourceAlphabet() {
    return this->sourceAlphabet;
}

void Coder::setP(std::string filename) {
    std::vector<std::string> strs = StringParser::getLineFromFile(filename);
    std::vector<float> nums;
    for (int i = 0; i < strs.size(); ++i) {
        nums.push_back(atof(strs.at(i).c_str()));
    }
    this->p = nums;
}

std::vector<float> Coder::getP() {
    return this->p;
}
//--
/*
 * Инициализации. Все буквы из алфавита записываются по убыванию
вероятностей встречаемости в сообщениях. Каждой букве ставится в
соответствие кумулятивная вероятность по правилу: q 1 0 , q 2 P 1 ,...,
*/
void Coder::sortAlphabetAndP() {
    for (int i = 0; i < this->p.size(); ++i) {
        for (int j = 0; j < this->p.size() - 1; ++j) {
            if (this->p.at(j) < this->p.at(j + 1)) {
                VectorUtil<float>::swapElements(&this->p, j, j+1);
                VectorUtil<std::string>::swapElements(&this->sourceAlphabet, j, j+1);
            }
        }
    }
}

//--
void Coder::setQ() {
    this->q.push_back(0);
    for (int i = 1; i < this->p.size(); ++i) {
        this->q.push_back(this->q.at(i - 1) + this->p.at(i - 1));
    }
}

std::vector<float> Coder::getQ() {
    return this->q;
}

void Coder::setL() {
    for (int i = 0; i < this->p.size(); ++i) {
        l.push_back( std::fabs( std::logb(this->p.at(i)) ) );
    }
}

std::vector<float> Coder::getL() {
    return this->l;
}

void Coder::setCode() {
    /*for (int k = 0; k < 6; k++) {
        code[k] = dec_to_bin(q[k], l[k]);
        cout << code[k] << endl;
    }*/
    for (int i = 0; i < this->q.size(); ++i) {
        this->code.push_back( this->decToBin( this->q.at(i), this->l.at(i) ));
    }
}

std::vector<std::string> Coder::getCode() {
    return this->code;
}

std::string Coder::decToBin(float num, int c) {
    float intpart;
    float buf = std::modf (num , &intpart);
    std::string cs = "";

    for (int i = 0; i < c; ++i) {
        buf = std::modf ( buf*2 , &intpart);
        cs+= std::to_string(intpart).substr(0,1);
    }

    return cs;
}

std::string Coder::codeMessage(std::vector<std::string> message) {
    std::vector<std::string> encMsg = std::vector<std::string>();
    std::string encrMsg;
    for (int i = 0; i < message.size(); ++i) {
        for (int j = 0; j < this->sourceAlphabet.size(); ++j) {
            if (message.at(i).compare(this->sourceAlphabet.at(j)) == 0) {
                encMsg.push_back(this->code.at(j));
                encrMsg += this->code.at(j);
            }
        }
    }

    return encrMsg;

}

void Coder::setLastEncryptedMessage (std::vector<std::string> lem) {
    this->lastEncryptedMessage = lem;
}

std::vector<std::string> Coder::getLastEncryptedMessage() {
    return this->lastEncryptedMessage;
}
/*
int indexOf(char alphabet[6], char ch) {
    int pos = -1;
    for (int i = 0; i < 6; i++) {
        if (alphabet[i] == ch) {
            pos = i;
            break;
        }
    }
    return pos;
}

string codeMessage(char alphabet[6], string code[6], char* message) {
    char cmesg[100];
    for (int i = 0; i < strlen(message); ++i) {
        int pos = indexOf(alphabet, message[i]);
        if (pos == -1) {
            break;
        }
        const char* cd = code[pos].c_str();
        if (i == 0) {
            strcpy(cmesg, cd);
        } else {
            strcat(cmesg, cd);
        }
    }

    return cmesg;
}


void funcMain() {

    cout << "Message is: " << "abbacdadde" << endl;
    cout << "Coded message is: " << codeMessage(x, code, "abbacdadde") << endl;
}
*/