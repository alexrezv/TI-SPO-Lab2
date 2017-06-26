#include <iostream>
#include <fstream>
#include <vector>
#include "util/Reader.h"
#include "Shennon_algorithm/Coder.h"
#include "Shennon_algorithm/Decoder.h"

using namespace std;

int main(int argc, char *argv[]) {
    const string actionCode = "code";
    const string actionDecode = "decode";

    if (!argv[1] || !argv[2]) {
        std::cerr << "usage: " << argv[0] << " <messageFile> <action>" << std::endl;
        std::cerr << "Make sure you have those files alongside the program file:\n"
                "\t\"alphabet\" - with alphabet used to write a message\n"
                "\t\"probabilityOfOccurrence\" - with probability of occurrence of the symbols of the alphabet\n"
                "Format of files - \"x1,x2,x3\" where each x in probabilityOfOccurrence file complies to an x in alphabet file\n"
                "Be sure to use coder at least once before trying to decode a message.\n";
        return 1;
    }

    if (actionCode.compare(argv[2]) == 0) {
        vector<string> message;
        StringParser sp = StringParser("alphabet");
        message = sp.parseMessage(Reader::readMessage(argv[1]));
        cout << "Input message is: \"" << Reader::readMessage(argv[1]) << "\"" << endl;
        Coder shC = Coder("alphabet", "probabilityOfOccurrence");

        cout << "-----------------------------------------------------------" << endl;
        cout << "Source alphabet: ";
        VectorUtil<string>::printVector(shC.getSourceAlphabet(), " , ");
        cout << "Probability: ";
        VectorUtil<float>::printVector(shC.getP(), " , ");
        cout << "Computed code: ";
        VectorUtil<std::string>::printVector(shC.getCode(), " , ");
        cout << "-----------------------------------------------------------" << endl;

        string codedMessage = shC.codeMessage(message);

        cout << "Coded message is: " << codedMessage << endl;
    }

    if (actionDecode.compare(argv[2]) == 0) {
        StringParser alphabetParser = StringParser("alphabet");
        StringParser codeParser = StringParser("code");
        Decoder shD = Decoder(alphabetParser.getSourceAlphabet(), codeParser.getSourceAlphabet());
        string message = Reader::readMessage(argv[1]);
        cout << "Coded message:\t" << message << endl;
        cout << "Decoded message:\t" << shD.decodeMessage(message) << endl;

    }

    return 0;
}