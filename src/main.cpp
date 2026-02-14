#include <iostream>
#include <string>
#include <cstring>

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

    cout << inputFile << " " << outputFile;
}