#include "parser.h"
#include <stdexcept>

static size_t current;
static std::vector<Token> toks;

static Token peek() { return toks[current]; }
static Token advance() { return toks[current++]; }
static bool match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

std::vector<Assignment> parse(const std::vector<Token>& tokens) {
    toks = tokens;
    current = 0;
    std::vector<Assignment> program;

    while (peek().type != TokenType::EndOfFile) {
        auto var = std::make_shared<Variable>();
        var->name = advance().text;

        if (!match(TokenType::Equals))
            throw std::runtime_error("Expected '='");

        Token func = advance(); // expect SQUAREADD

        if (func.text != "SQUAREADD")
            throw std::runtime_error("Expected 'SQUAREADD'");

        if (!match(TokenType::LParen))
            throw std::runtime_error("Expected '('");

        auto arg1 = std::make_shared<Variable>();
        arg1->name = advance().text;

        if (!match(TokenType::Comma))
            throw std::runtime_error("Expected ','");

        auto arg2 = std::make_shared<Variable>();
        arg2->name = advance().text;

        if (!match(TokenType::RParen))
            throw std::runtime_error("Expected ')'");

        auto expr = std::make_shared<SquareAddExpr>();
        expr->arg1 = arg1;
        expr->arg2 = arg2;

        Assignment assign;
        assign.target = var;
        assign.expr = expr;
        program.push_back(assign);
    }

    return program;
}