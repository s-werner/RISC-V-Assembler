#include "../include/encoder.h"
#include "../include/instructions.h"
#include <iostream>
#include <sstream>

using namespace std;

struct OffsetRegister {
    uint32_t reg;
    int32_t offset;
};

uint32_t parseRegister(string reg) {
    if (reg[0] != 'x') {
        cerr << "Expected register, received: " << reg << endl;
        return 0;
    }

    uint32_t regNum = stoi(reg.substr(1, reg.size()));

    if (regNum > 31) {
        cerr << "Invalid register number: " << regNum << endl;
        return 0;
    }

    return regNum;
}

OffsetRegister parseOffsetRegister(string token) {
    size_t openParenthesisIndex = token.find('(');

    if (openParenthesisIndex == string::npos) {
        cerr << "Invalid offset format, expected offset(register)" << endl;
        return {0, 0};
    }

    string regStr = token.substr(openParenthesisIndex + 1);
    regStr.pop_back();

    uint32_t reg = parseRegister(regStr);
    int32_t imm = stoi(token.substr(0, openParenthesisIndex));

    return {
        reg,
        imm
    };
}

uint32_t encodeRType (InstructionInfo info, vector<string> tokens) {
    uint32_t instruction = 0;
    vector<uint32_t> registers;

    for(int i = 1; i < tokens.size(); i++) {
        uint32_t parsedRegister = parseRegister(tokens[i]);
        registers.push_back(parsedRegister);
    }

    if (registers.size() != 3) {
        cerr << "Invalid number of registers: " << registers.size();
        return 0;
    }

    instruction |= info.opcode;
    instruction |= (registers[0] << 7);
    instruction |= (info.funct3 << 12);
    instruction |= (registers[1] << 15);
    instruction |= (registers[2] << 20);
    instruction |= (info.funct7 << 25);

    return instruction;
}

uint32_t encodeIType (InstructionInfo info, vector<string> tokens) {
    uint32_t instruction = 0;
    vector<uint32_t> registers;

    if (tokens.size() != 4) {
        cerr << "Invalid number of tokens: " << tokens.size() << endl;
        return 0;
    }

    for(int i = 1; i < tokens.size()-1; i++) {
        uint32_t parsedRegister = parseRegister(tokens[i]);
        registers.push_back(parsedRegister);
    }

    if (registers.size() != 2) {
        cerr << "Invalid number of registers: " << registers.size();
        return 0;
    }

    int32_t immediate = stoi(tokens.back());

    instruction |= info.opcode;
    instruction |= (registers[0] << 7);
    instruction |= (info.funct3 << 12);
    instruction |= (registers[1] << 15);
    instruction |= ((immediate & 0xFFF) << 20);

    return instruction;
}

uint32_t encodeSType (InstructionInfo info, vector<string> tokens) {
    uint32_t instruction = 0;

    if (tokens.size() != 3) {
        cerr << "Invalid number of tokens: " << tokens.size() << endl;
        return 0;
    }

    uint32_t rs2 = parseRegister(tokens[1]);
    OffsetRegister offReg = parseOffsetRegister(tokens[2]);

    instruction |= info.opcode;
    instruction |= ((offReg.offset & 0x1F) << 7);
    instruction |= (info.funct3 << 12);
    instruction |= (offReg.reg << 15);
    instruction |= (rs2 << 20);
    instruction |= (((offReg.offset >> 5) & 0x7F) << 25);;

    return instruction;
}

uint32_t encodeBType (InstructionInfo info, vector<string> tokens) {
    uint32_t instruction = 0;

    if (tokens.size() != 4) {
        cerr << "Invalid number of tokens: " << tokens.size() << endl;
        return 0;
    }

    uint32_t rs1 = parseRegister(tokens[1]);
    uint32_t rs2 = parseRegister(tokens[2]);
    int32_t imm = stoi(tokens[3]);

    instruction |= info.opcode;
    instruction |= ((imm & 0x800) >> 4);
    instruction |= ((imm & 0x1E) << 7);
    instruction |= (info.funct3 << 12);
    instruction |= (rs1 << 15);
    instruction |= (rs2 << 20);
    instruction |= ((imm & 0x7E0) << 20);
    instruction |= ((imm & 0x1000) << 19);

    return instruction;
}

uint32_t encode (vector<string> tokens) {
    string instruction = tokens[0];
    uint32_t encodedInstruction;

    if (instructionTable.find(instruction) == instructionTable.end()) {
        cerr << "Error: Unknown instruction: " << instruction << endl;
        return 0;
    }

    InstructionInfo info = instructionTable[instruction];
    
    switch(info.type) {
        case R_TYPE: return encodeRType(info, tokens);
        case I_TYPE: return encodeIType(info, tokens);
        case S_TYPE: return encodeSType(info, tokens);
        case B_TYPE: return encodeBType(info, tokens);
        default:
            cerr << "Unsupported instruction type" << endl;
            return 0;
    }

    return encodedInstruction;
}