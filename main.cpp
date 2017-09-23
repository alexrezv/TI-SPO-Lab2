#include <iostream>
#include <fstream>
#include <vector>
#include "util/Reader.h"
#include "Shennon_algorithm/Coder.h"
#include "Shennon_algorithm/Decoder.h"
#include "CodeRater/CodeRater.h"

using namespace std;

void doCode(std::string, bool);

void doDecode(std::string);

void printStats(Coder);

int main(int argc, char *argv[]) {
    const string actionCode = "code";
    const string actionDecode = "decode";
    const string optionStats = "-s";

    int argsSize = sizeof(argv);

    if (!argv[1] || !argv[2]) {
        std::cerr << "usage: " << argv[0] << " [option] <messageFile> <action>" << std::endl;
        std::cerr << "Make sure you have those files alongside the program file:\n"
                "\t\"alphabet\" - with alphabet used to write a message\n"
                "\t\"probabilityOfOccurrence\" - with probability of occurrence of the symbols of the alphabet\n"
                "Format of files - \"x1,x2,x3\" where each x in probabilityOfOccurrence file complies to an x in alphabet file\n"
                "Be sure to use coder at least once before trying to decode a message.\n"
                "Recognizable actions: \"code\" and \"decode\".\n"
                "Available option: \"-s\" - show statistics for the generated code.\n";
        return 1;
    }

    if (actionDecode.compare(argv[2]) == 0) {
        doDecode(argv[1]);
        return 0;
    }

    if (actionCode.compare(argv[2]) == 0) {
        doCode(argv[1], false);
        return 0;
    } else if (actionCode.compare(argv[3]) == 0 && optionStats.compare(argv[1]) == 0) {
        doCode(argv[2], true);
        return 0;
    }

    if (optionStats.compare(argv[1]) == 0 && actionDecode.compare(argv[2]) == 0) {
        std::cerr << "You shouldn't use \"-s\" option with \"decode\" action" << endl;
        return 1;
    }



    return 0;
}

void doCode(string filename, bool stats) {
    vector<string> message;
    StringParser sp = StringParser("alphabet");
    message = sp.parseMessage(Reader::readMessage(filename));
    cout << "┌───────────────────────────────────────────────────────────" << endl;
    cout << "│  Input message is: \"" << Reader::readMessage(filename) << "\"" << endl;
    Coder shC = Coder("alphabet", "probabilityOfOccurrence");

    cout << "├───────────────────────────────────────────────────────────" << endl;
    cout << "│  Source alphabet: ";
    VectorUtil<string>::printVector(shC.getSourceAlphabet(), " , ");
    cout << "│  Probability: ";
    VectorUtil<double>::printVector(shC.getP(), " , ");
    cout << "│  Computed code: ";
    VectorUtil<std::string>::printVector(shC.getCode(), " , ");
    cout << "├───────────────────────────────────────────────────────────" << endl;

    string codedMessage = shC.codeMessage(message);

    cout << "│  Coded message is: " << codedMessage << endl;
    cout << "└───────────────────────────────────────────────────────────" << endl;

    if (stats) {
        printStats(shC);
    }
}

void doDecode(string filename) {
    StringParser alphabetParser = StringParser("alphabet");
    StringParser codeParser = StringParser("code");
    Decoder shD = Decoder(alphabetParser.getSourceAlphabet(), codeParser.getSourceAlphabet());
    string message = Reader::readMessage(filename);
    cout << "Coded message:\t" << message << endl;
    cout << "Decoded message:\t" << shD.decodeMessage(message) << endl;
}

void printStats(Coder coder) {
    cout << "┌─────────────────────────────────────┐" << endl;
    cout << "│          GENERATED CODE INFO        │" << endl;
    cout << "├───────────────────────────┬─────────┤" << endl;
    CodeRater cr = CodeRater(coder.getP(), coder.getCode());
    cr.printCodeRate();
    cout << "└─────────────────────────────────────┘" << endl;
}