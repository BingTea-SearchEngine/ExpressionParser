// test program
#include <iostream>

#include "expression.hpp"
#include "Parser.hpp"

int main(){
    std::string input; // example: ( dogs AND cats birds ) NOT " good pets "
    std::getline(std::cin, input);

    Parser parser(input);

    Expression *expr = parser.Parse();

    if(expr){
        std::cout << expr->Eval() << std::endl; // currently outputs a nested ISR structure as a string
        delete expr;
    }
    else{
        std::cout << "Syntax error" << std::endl;
    }
}