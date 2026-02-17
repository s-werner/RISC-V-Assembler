#include "../include/encoder.h"
#include "../include/instructions.h"

using namespace std;

uint32_t encode (vector<string> tokens) {
    string instruction = tokens[0];
    uint32_t encodedInstruction;

    if (instructionTable.find(instruction) == instructionTable.end()) {
        cerr << "Error: Unknown instruction: " << instruction << endl;
        return 0;
    }

    InstructionInfo instructionInfo = instructionTable[instruction];
    
    return encodedInstruction;
}