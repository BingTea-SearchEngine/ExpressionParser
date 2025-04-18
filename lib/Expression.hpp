#pragma once

#include <stdint.h>
#include <vector>
#include <string>

// base class
class Expression {
public:

   virtual ~Expression();
   virtual std::string Eval() const = 0; // placeholder for actual ISRs

};
// class Expression

// <Constraint> ::= <BaseConstraint> { <OrOp> <BaseConstraint> }
class Constraint: public Expression {
protected:

   std::vector<Expression*> BCs;

public:

   Constraint(std::vector<Expression*> BCin);
   ~Constraint();
   std::string Eval() const override;
};
// class Constraint

// <BaseConstraint> ::= <SimpleConstraint> { [ <AndOp> ] <SimpleConstraint> } | <SimpleConstraint> <NotOp> <SimpleConstraint>
class BaseConstraint: public Expression {
protected:

   std::vector<Expression*> SCs;
   std::string type;

public:

   BaseConstraint(std::vector<Expression*> SCin, std::string typein);
   ~BaseConstraint();
   std::string Eval() const override;

};
// class BaseConstraint

// <SimpleConstraint> ::= <Phrase> | <NestedConstraint> | <NotConstraint> | <SearchWord>
class SimpleConstraint: public Expression {
protected:

   Expression* inner;

public:

   SimpleConstraint(Expression* innerin);
   ~SimpleConstraint();
   std::string Eval() const override;

};
// class SimpleConstraint

// <Phrase> ::= '"' { <SearchWord> } '"'
class Phrase: public Expression {
protected:

    std::vector<Expression*> SWs;

public:

    Phrase(std::vector<Expression*> SWin);
    ~Phrase();
    std::string Eval() const override;

};
// class Phrase

// <NestedConstraint> ::= '(' <Constraint> ')'
class NestedConstraint: public Expression {
protected:

    Expression* inner;

public:

    NestedConstraint(Expression* innerin);
    ~NestedConstraint();
    std::string Eval() const override;
    
};
// class NestedConstraint

// <SearchWord> lowest level
class SearchWord: public Expression {
protected:

    std::string value;

public:

    SearchWord(std::string valuein);
    std::string Eval() const override;
    
};
// class SearchWord
