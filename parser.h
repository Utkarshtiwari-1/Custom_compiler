#pragma once
#include "tokenizer.h"
#include "ast.h"
#include <vector>

std::vector<Assignment> parse(const std::vector<Token>& tokens);