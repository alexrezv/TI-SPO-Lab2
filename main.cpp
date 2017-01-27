#include <iostream>
#include <fstream>
#include <vector>
#include "StringParser/StringParser.h"
#include "Shennon_algorithm/Coder.h"
#include "Shennon_algorithm/Decoder.h"
#include "util/VectorUtil.h"

using namespace std;

string readMessage();

int main(int argc, char *argv[]) {

    /*if(!argv[1]) {
        std::cerr << "usage: " << argv[0] << " inputfilename action" << std::endl;
        std::cerr << "Make sure you have those files alongside the program file:\n"
                "\t\"alphabet\" - with alphabet used to write a message\n"
                "\t\"probabilityOfOccurrence\" - with probability of occurrence of the symbols of the alphabet\n"
                "Format of files - \"x1,x2,x3\" where each x in pOO-file complies to an x in alphabet-file\n";
        return 1;
    }

    if (argv[2])*/

    vector<string> message;
    StringParser sp = StringParser("alphabet");
    message = sp.parseMessage(readMessage());
    Coder shC = Coder("alphabet", "probabilityOfOccurrence");
    cout << shC.codeMessage(message) << endl;
    Decoder shD = Decoder(shC.getSourceAlphabet(), shC.getCode());
    cout << shD.decodeMessage(shC.codeMessage(message)) << endl;



    return 0;
}

string readMessage() {
    ifstream f_message;
    f_message.open("message", ios::in);

    string message = "";
    getline(f_message, message);

    return message;
}