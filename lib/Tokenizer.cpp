#include <cctype>
#include <sstream>
#include <algorithm>
#include <iostream>

#include "Tokenizer.hpp"


Tokenstream::Tokenstream(const std::string &input){
    head = nullptr;
    end = nullptr;
    Tokenize(input);
}

Token* Tokenstream::GetHead() const{
    return head;
}

Token* Tokenstream::MatchToken(TokenType typein){
    // returns and consumes the head token if it matches the type
    if (head && head->type == typein){
        Token* current = head;
        head = head->next;
        current->next = nullptr;
        return current;
    }
    return nullptr;
}

void Tokenstream::AppendToken(TokenType type, const std::string& value){
    Token* t = new Token{type, value};

    if(!head && !end){ // first token
        head = t;
        end = t;
    }
    else{
        end->next = t;
        end = t;
    }

}

void Tokenstream::Tokenize(const std::string& input){
    std::istringstream iss(input);
    std::string curr;
    while(iss >> curr){ // for now all operations have to be seperated by a space eg no "dog|cat"
        if(curr == "|" || curr == "||" || curr == "OR"){
            AppendToken(TokenType::OROP, "");
        }
        else if(curr == "&" || curr == "&&" || curr == "AND"){
            AppendToken(TokenType::ANDOP, "");
        }
        else if(curr == "\""){
            AppendToken(TokenType::QUOTE, "");
        }
        else if(curr == "("){
            AppendToken(TokenType::LPAREN, "");
        }
        else if(curr == ")"){
            AppendToken(TokenType::RPAREN, "");
        }
        else if(curr == "NOT" || curr == "-"){
            AppendToken(TokenType::UNARYOP, "-");
        }
        else if(curr == "+"){
            AppendToken(TokenType::UNARYOP, "+");
        }
        else{
            AppendToken(TokenType::WORD, curr);
        }
    }
    AppendToken(TokenType::END, "");
}

// debugging function
void Tokenstream::PrintTokens(){
    Token* curr = head;
    while(curr->type != TokenType::END){
        if(curr->type == TokenType::OROP){
            std::cout<<" OR";
        }
        else if(curr->type == TokenType::QUOTE){
            std::cout<<" \"";
        }
        else if(curr->type == TokenType::ANDOP){
            std::cout<<" AND";
        }
        else if(curr->type == TokenType::LPAREN){
            std::cout<<" (";
        }
        else if(curr->type == TokenType::RPAREN){
            std::cout<<" )";
        }
        else if(curr->type == TokenType::WORD || curr->type == TokenType::UNARYOP){
            std::cout<<" "<<curr->value;
        }
        curr = curr->next;
    }
    std::cout<<std::endl;
}