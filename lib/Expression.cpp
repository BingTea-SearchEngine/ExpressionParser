#include "Expression.hpp"
#include <sstream>

Expression::~Expression(){}

// <Constraint> ::= <BaseConstraint> { <OrOp> <BaseConstraint> }
Constraint::Constraint(std::vector<Expression*> BCin): BCs(BCin) {}

Constraint::~Constraint(){
    for(int i = 0; i < BCs.size(); i++){
        delete BCs[i];
    }
}

std::string Constraint::Eval() const{ // placeholder for an OR ISR
    if(BCs.size() == 1){ // collapse level if there is only one child
        return BCs[0]->Eval();
    }
    std::stringstream ss;
    ss << "OrISR(";
    for(int i = 0; i < BCs.size(); i++){
        if(i > 0){
            ss << ", ";
        }
        ss << BCs[i]->Eval();
    }
    ss <<")";
    return ss.str();
}
// class Constraint

// <BaseConstraint> ::= <SimpleConstraint> { [ <AndOp> ] <SimpleConstraint> } | <SimpleConstraint> <NotOp> <SimpleConstraint>
BaseConstraint::BaseConstraint(std::vector<Expression*> SCin, std::string typein): SCs(SCin), type(typein) {}

BaseConstraint::~BaseConstraint(){
    for(int i = 0; i < SCs.size(); i++){
        delete SCs[i];
    }
}

std::string BaseConstraint::Eval() const{
    if(SCs.size() == 1){ // collapse level if there is only one child
        return SCs[0]->Eval();
    }
    if(type == "And"){
        std::stringstream ss;
        ss << "AndISR(";
        for(int i = 0; i < SCs.size(); i++){
            if(i > 0){
                ss << ", ";
            }
            ss << SCs[i]->Eval();
        }
        ss <<")";
        return ss.str();
    }
    else if(type == "Not"){ // not ISR only has two fields
        return "NotISR(" + SCs[0]->Eval() + ", " + SCs[1]->Eval() + ")";
    }
}
// class BaseConstraint

// <SimpleConstraint> ::= <Phrase> | <NestedConstraint> | <NotConstraint> | <SearchWord>
SimpleConstraint::SimpleConstraint(Expression* innerin): inner(innerin) {}
   
SimpleConstraint::~SimpleConstraint(){
    delete inner;
}

std::string SimpleConstraint::Eval() const{ // this just needs to evaluate inner
    return inner->Eval();
}
// class SimpleConstraint

// <Phrase> ::= '"' { <SearchWord> } '"'
Phrase::Phrase(std::vector<Expression*> SWin): SWs(SWin) {}

Phrase::~Phrase(){
    for(int i = 0; i < SWs.size(); i++){
        delete SWs[i];
    }
}
    
std::string Phrase::Eval() const{ // placeholder for a PHRASE ISR
    if(SWs.size() == 1){ // collapse level if there is only one child
        return SWs[0]->Eval();
    }
    std::stringstream ss;
    ss << "PhraseISR(";
    for(int i = 0; i < SWs.size(); i++){
        if(i > 0){
            ss << ", ";
        }
        ss << SWs[i]->Eval();
    }
    ss <<")";
    return ss.str();
}
// class Phrase

// <NestedConstraint> ::= '(' <Constraint> ')'
NestedConstraint::NestedConstraint(Expression* innerin): inner(innerin) {}

NestedConstraint::~NestedConstraint(){
    delete inner;
}
        
std::string NestedConstraint::Eval() const{ // just needs to eval inner
    return inner->Eval();
}
// class NestedConstraint

// <SearchWord> lowest level
SearchWord::SearchWord(std::string valuein): value(valuein) {}
        
std::string SearchWord::Eval() const{ // placeholder for an OR ISR
    return "WordISR(" + value + ")";
}
// class SearchWord
