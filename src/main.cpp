#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
#include "lexer.h"
#include "encoder.h"

using namespace std;

int main(int argc, char* argv[]) {
    string inputFile, outputFile;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                outputFile = argv[i+1];
                i++;
            } else {
                cerr << "Error: No output file after '-o'";
                return 1;
            }
        } else {
            inputFile = argv[i];
        }
    }

    if (inputFile.empty()) {
        cerr << "Error: No input file";
        return 1;
    }

    if (outputFile.empty()) {
        outputFile = "output.hex";
    }

    cout << inputFile << " " << outputFile << "\n";

    vector<string> instructions = {
        "sra x0, x1, x4",
        "sw x1, 4(x4)",
        "beq x1 x2 4",
    };

    for (int i = 0; i < instructions.size(); i++) {
        vector<string> tokens = lexer(instructions[i]);
        for (string token : tokens) {
            cout << token << " ";
        }

        uint32_t encoded = encode(tokens);
        cout << "\nEncoded instruction: 0x" << std::hex << encoded << std::dec << "\n";
        cout << hex << setfill('0') << setw(8) << instructions[i] << endl;
    }
}
