#include <gtest/gtest.h>
#include "../include/encoder.h"
#include "../include/lexer.h"

using namespace std;

TEST(EncoderTest, AddInstruction) {
    vector<string> tokens = {"add", "x1", "x2", "x3"};
    uint32_t result = encode(tokens);
    EXPECT_EQ(result, 0x003100b3);
}

TEST(EncoderTest, AddiInstruction) {
    vector<string> tokens = {"addi", "x1", "x0", "5"};
    uint32_t result = encode(tokens);
    EXPECT_EQ(result, 0x00500093);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}