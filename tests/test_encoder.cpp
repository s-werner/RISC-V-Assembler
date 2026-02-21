#include <gtest/gtest.h>
#include "../include/encoder.h"
#include "../include/lexer.h"

using namespace std;

// R-Type Tests
TEST(RTypeTest, ADD) {
    vector<string> tokens = {"add", "x1", "x2", "x3"};
    EXPECT_EQ(encode(tokens), 0x003100b3);
}

TEST(RTypeTest, SUB) {
    vector<string> tokens = {"sub", "x4", "x5", "x6"};
    EXPECT_EQ(encode(tokens), 0x40628233);
}

TEST(RTypeTest, SLL) {
    vector<string> tokens = {"sll", "x7", "x8", "x9"};
    EXPECT_EQ(encode(tokens), 0x009413b3);
}

TEST(RTypeTest, SLT) {
    vector<string> tokens = {"slt", "x10", "x11", "x12"};
    EXPECT_EQ(encode(tokens), 0x00c5a533);
}

TEST(RTypeTest, SLTU) {
    vector<string> tokens = {"sltu", "x13", "x14", "x15"};
    EXPECT_EQ(encode(tokens), 0x00f736b3);
}

TEST(RTypeTest, XOR) {
    vector<string> tokens = {"xor", "x16", "x17", "x18"};
    EXPECT_EQ(encode(tokens), 0x0128c833);
}

TEST(RTypeTest, SRL) {
    vector<string> tokens = {"srl", "x19", "x20", "x21"};
    EXPECT_EQ(encode(tokens), 0x015a59b3);
}

TEST(RTypeTest, SRA) {
    vector<string> tokens = {"sra", "x22", "x23", "x24"};
    EXPECT_EQ(encode(tokens), 0x418bdb33);
}

TEST(RTypeTest, OR) {
    vector<string> tokens = {"or", "x25", "x26", "x27"};
    EXPECT_EQ(encode(tokens), 0x01bd6cb3);
}

TEST(RTypeTest, AND) {
    vector<string> tokens = {"and", "x28", "x29", "x30"};
    EXPECT_EQ(encode(tokens), 0x01eefe33);
}

// I-Type ALU Tests
TEST(ITypeALUTest, ADDI) {
    vector<string> tokens = {"addi", "x1", "x0", "5"};
    EXPECT_EQ(encode(tokens), 0x00500093);
}

TEST(ITypeALUTest, SLTI) {
    vector<string> tokens = {"slti", "x2", "x3", "10"};
    EXPECT_EQ(encode(tokens), 0x00a1a113);
}

TEST(ITypeALUTest, SLTIU) {
    vector<string> tokens = {"sltiu", "x4", "x5", "15"};
    EXPECT_EQ(encode(tokens), 0x00f2b213);
}

TEST(ITypeALUTest, XORI) {
    vector<string> tokens = {"xori", "x6", "x7", "20"};
    EXPECT_EQ(encode(tokens), 0x0143c313);
}

TEST(ITypeALUTest, ORI) {
    vector<string> tokens = {"ori", "x8", "x9", "25"};
    EXPECT_EQ(encode(tokens), 0x0194e413);
}

TEST(ITypeALUTest, ANDI) {
    vector<string> tokens = {"andi", "x10", "x11", "30"};
    EXPECT_EQ(encode(tokens), 0x01e5f513);
}

// I-Type Load Tests
TEST(ITypeLoadTest, LB) {
    vector<string> tokens = {"lb", "x1", "4(x2)"};
    EXPECT_EQ(encode(tokens), 0x00410083);
}

TEST(ITypeLoadTest, LH) {
    vector<string> tokens = {"lh", "x3", "8(x4)"};
    EXPECT_EQ(encode(tokens), 0x00821183);
}

TEST(ITypeLoadTest, LW) {
    vector<string> tokens = {"lw", "x5", "12(x6)"};
    EXPECT_EQ(encode(tokens), 0x00c32283);
}

TEST(ITypeLoadTest, LBU) {
    vector<string> tokens = {"lbu", "x7", "16(x8)"};
    EXPECT_EQ(encode(tokens), 0x01044383);
}

TEST(ITypeLoadTest, LHU) {
    vector<string> tokens = {"lhu", "x9", "20(x10)"};
    EXPECT_EQ(encode(tokens), 0x01455483);
}

// S-Type Store Tests
TEST(STypeTest, SB) {
    vector<string> tokens = {"sb", "x1", "0(x2)"};
    EXPECT_EQ(encode(tokens), 0x00110023);
}

TEST(STypeTest, SH) {
    vector<string> tokens = {"sh", "x3", "4(x4)"};
    EXPECT_EQ(encode(tokens), 0x00321223);
}

TEST(STypeTest, SW) {
    vector<string> tokens = {"sw", "x5", "8(x6)"};
    EXPECT_EQ(encode(tokens), 0x00532423);
}

// B-Type Branch Tests
TEST(BTypeTest, BNE) {
    vector<string> tokens = {"bne", "x1", "x2", "8"};
    EXPECT_EQ(encode(tokens), 0x00209463);
}

TEST(BTypeTest, BLT) {
    vector<string> tokens = {"blt", "x3", "x4", "12"};
    EXPECT_EQ(encode(tokens), 0x0041c663);
}

TEST(BTypeTest, BGE) {
    vector<string> tokens = {"bge", "x5", "x6", "16"};
    EXPECT_EQ(encode(tokens), 0x0062d863);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}