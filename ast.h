#pragma once
#include <string>
#include <memory>

struct Variable {
    std::string name;
};

struct Expression {
    virtual ~Expression() = default;
};

struct SquareAddExpr : Expression {
    std::shared_ptr<Variable> arg1, arg2;
};

struct Assignment {
    std::shared_ptr<Variable> target;
    std::shared_ptr<Expression> expr;
};