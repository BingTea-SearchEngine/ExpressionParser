// test program
#include <iostream>

#include "expression.hpp"
#include "Parser.hpp"

int main(){
    std::string input;
    std::getline(std::cin, input);

    Parser parser(input);

    Expression *expr = parser.Parse();

    if(expr){
        std::cout << expr->Eval() << std::endl;
        delete expr;
    }
    else{
        std::cout << "Syntax error" << std::endl;
    }
}