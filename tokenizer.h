#pragma once
#include <vector>
#include <string>

enum class TokenType {
    Identifier,
    Equals,
    Comma,
    LParen,
    RParen,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string text;
};

std::vector<Token> tokenize(const std::string& input);