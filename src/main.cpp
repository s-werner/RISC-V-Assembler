#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <iomanip>
#include <fstream>

#include "lexer.h"
#include "encoder.h"

using namespace std;

int main(int argc, char* argv[]) {
    string inputFilePath, outputFilePath;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                outputFilePath = argv[i+1];
                i++;
            } else {
                cerr << "Error: No output file after '-o'";
                return 1;
            }
        } else {
            inputFilePath = argv[i];
        }
    }

    if (inputFilePath.empty()) {
        cerr << "Error: No input file";
        return 1;
    }
    if (outputFilePath.empty()) {
        outputFilePath = "output.hex";
    }

    ifstream inputFile(inputFilePath);
    string line;
    vector<string> instructions;

    while (getline(inputFile, line)) {
        if (!line.empty()) {
            instructions.push_back(line);
        }
    }
    inputFile.close();

    vector<uint32_t> encodedInstructions;
    for (int i = 0; i < instructions.size(); i++) {
        vector<string> tokens = lexer(instructions[i]);
        uint32_t encoded = encode(tokens);

        encodedInstructions.push_back(encoded);

        cout << "\nEncoded instruction: 0x" << std::hex << encoded << std::dec << "\n";
        cout << hex << setfill('0') << setw(8) << instructions[i] << endl;
    }

    ofstream outputFile(outputFilePath);
    for (int i = 0; i < encodedInstructions.size(); i++) {
        outputFile << "instr_mem[" << i << "] = 32'h" 
                << hex << setfill('0') << setw(8) 
                << encodedInstructions[i] 
                << ";" << endl;
    }
}
