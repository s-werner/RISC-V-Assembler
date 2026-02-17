#include "../include/lexer.h"

using namespace std;

vector<string> lexer (string instruction) {
    vector<string> tokens;
    stringstream ss(instruction);
    string token;

    while (ss >> token) {
        if (token.back() == ',') {
            token.pop_back();
        }
        tokens.push_back(token);
    }

    return tokens;
}