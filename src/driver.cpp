// test program
#include <iostream>

#include "Expression.hpp"
#include "Parser.hpp"

int main(){
    std::string input; // example: (dogs AND cats birds) NOT "good pets"
    std::getline(std::cin, input);
    std::cout<<"Hello"<<std::endl;

    Parser parser(input);
    std::cout<<"Hello2"<<std::endl;

    Expression *expr = parser.Parse();
    std::cout<<"Hello3"<<std::endl;

    if(expr){
        std::cout << expr->Eval() << std::endl; // currently outputs a nested ISR structure as a string
        delete expr;
    }
    else{
        std::cout << "Syntax error" << std::endl;
    }
}
