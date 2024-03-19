//
// Created by Lindsay Haslam on 2/16/24.
//
#pragma once

//#ifndef EXPRESSIONCLASSES_PARSE_HPP
#define EXPRESSIONCLASSES_PARSE_HPP

#include <iostream>
#include "Expr.h"

Expr* parse_num(std::istream &in);
Expr *parse_multicand(std::istream& in);
Expr *parse_expr(std::istream &in);
Expr *parse_expr(const std::string &in);
Expr *parse_addend(std::istream &in);
Expr * parse_bool( std::istream & stream );
Expr * parse_if ( std::istream & stream );
Expr * parse_eqs ( std::istream & stream );
Expr * parse_comparg( std::istream & stream );
void consume(std::istream &in, int expect);
void consume( std::istream & stream, const std::string & str);
static void consumeWord(std::istream &in, std::string word);
static string parse_term(istream &in);
void skip_whitespace(std::istream &in);
Expr *parse(std::istream &in);
Expr *parse_str(string s);
Expr *parse_var(std::istream &in);
Expr *parse_let(std::istream &in);
static void consumeWord(std::istream &in, std::string word);
Expr *parseInput();
std::string peek_keyword(std::istream &in);



//#endif //EXPRESSIONCLASSES_PARSE_HPP
