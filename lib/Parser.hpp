#pragma once

#include "Tokenizer.hpp"
#include "expression.hpp"
#include <string>

class Parser {
private:
    Tokenstream stream; // tokenstream to parse

    // Find various parts of the grammar, return nullptr if not found
    Expression *FindConstraint();

    Expression *FindBaseConstraint();

    Expression *FindSimpleConstraint();

    Expression *FindPhrase();

    Expression *FindNestedConstraint();

    Expression *FindSearchWord();

public:
    // construct stream based on a query
    Parser(const std::string &query);

    // Builds the tree
    Expression *Parse();
};