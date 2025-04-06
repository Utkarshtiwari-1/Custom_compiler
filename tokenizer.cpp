#include "tokenizer.h"
#include <cctype>

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < input.size()) {
        if (std::isspace(input[i])) {
            ++i;
        } else if (std::isalpha(input[i])) {
            std::string ident;
            while (i < input.size() && std::isalnum(input[i]))
                ident += input[i++];
            tokens.push_back({TokenType::Identifier, ident});
        } else if (input[i] == '=') {
            tokens.push_back({TokenType::Equals, "="});
            ++i;
        } else if (input[i] == '(') {
            tokens.push_back({TokenType::LParen, "("});
            ++i;
        } else if (input[i] == ')') {
            tokens.push_back({TokenType::RParen, ")"});
            ++i;
        } else if (input[i] == ',') {
            tokens.push_back({TokenType::Comma, ","});
            ++i;
        } else {
            ++i; // skip unknown chars
        }
    }

    tokens.push_back({TokenType::EndOfFile, ""});
    return tokens;
}