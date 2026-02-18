#include <map>
#include <cstdint>

enum InstructionType {
    R_TYPE,
    I_TYPE,
    S_TYPE,
    B_TYPE,
};

struct InstructionInfo {
    InstructionType type;
    uint32_t opcode;
    uint32_t funct3;
    uint32_t funct7;
};

std::map<std::string, InstructionInfo> instructionTable = {
    // R-type (opcode 0x33)
    {"add",  {R_TYPE, 0x33, 0x0, 0x00}},
    {"sub",  {R_TYPE, 0x33, 0x0, 0x20}},
    {"sll",  {R_TYPE, 0x33, 0x1, 0x00}},
    {"slt",  {R_TYPE, 0x33, 0x2, 0x00}},
    {"sltu", {R_TYPE, 0x33, 0x3, 0x00}},
    {"xor",  {R_TYPE, 0x33, 0x4, 0x00}},
    {"srl",  {R_TYPE, 0x33, 0x5, 0x00}},
    {"sra",  {R_TYPE, 0x33, 0x5, 0x20}},
    {"or",   {R_TYPE, 0x33, 0x6, 0x00}},
    {"and",  {R_TYPE, 0x33, 0x7, 0x00}},
    
    // I-type ALU (opcode 0x13)
    {"addi",  {I_TYPE, 0x13, 0x0, 0x00}},
    {"slti",  {I_TYPE, 0x13, 0x2, 0x00}},
    {"sltiu", {I_TYPE, 0x13, 0x3, 0x00}},
    {"xori",  {I_TYPE, 0x13, 0x4, 0x00}},
    {"ori",   {I_TYPE, 0x13, 0x6, 0x00}},
    {"andi",  {I_TYPE, 0x13, 0x7, 0x00}},
    
    // I-type loads (opcode 0x03)
    {"lw",   {I_TYPE, 0x03, 0x2, 0x00}},
    
    // S-type stores (opcode 0x23)
    {"sw",   {S_TYPE, 0x23, 0x2, 0x00}},
    
    // B-type branches (opcode 0x63)
    {"beq",  {B_TYPE, 0x63, 0x0, 0x00}}
};