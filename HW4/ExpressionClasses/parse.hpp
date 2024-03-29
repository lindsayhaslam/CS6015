//
// Created by Lindsay Haslam on 2/16/24.
//
#pragma once

//#ifndef EXPRESSIONCLASSES_PARSE_HPP
#define EXPRESSIONCLASSES_PARSE_HPP

#include <iostream>
#include "Expr.h"
#include "pointer.h"

//Expr *parse_str(string s);
//
//Expr *parse(istream &in);
//
//Expr *parse_expr(istream &in);
//
//Expr *parse_comparg(istream &in);
//
//Expr *parse_addend(istream &in);
//
//static string parse_term(istream &in);
//
//Expr *parse_multicand(istream &in);
//
//Expr *parse_num(istream &in);
//
//static void consume(istream &in, int expect);
//
//void consume(std::istream & stream, const std::string & str);
//
//static void skip_whitespace(istream &in);
//
//Expr *parse_variable(std::istream &in);
//
//std::string parse_var_name(std::istream &in);
//
//Expr *parse_let(istream &in);
//
//Expr* parse_if(istream &in);
//
//Expr* parse_bool(std::istream &in);
//
//Expr* parse_fun(istream &in);
//
//Expr* parse_inner(istream &in);

//LINDSAY

PTR(Expr) parse_num(std::istream &in);
PTR(Expr) parse_multicand(std::istream& in);
PTR(Expr) parse_expr(std::istream &in);
PTR(Expr) parse_expr(const std::string &in);
PTR(Expr) parse_addend(std::istream &in);
PTR(Expr) parse_bool( std::istream & stream );
PTR(Expr) parse_if ( std::istream & stream );
PTR(Expr) parse_eqs ( std::istream & stream );
PTR(Expr) parse_comparg( std::istream & stream );
void consume(std::istream &in, int expect);
void consume( std::istream & stream, const std::string & str);
static void consumeWord(std::istream &in, std::string word);
static string parse_term(istream &in);
void skip_whitespace(std::istream &in);
PTR(Expr) parse(std::istream &in);
PTR(Expr) parse_str(const string& s);
PTR(Expr) parse_var(std::istream &in);
PTR(Expr) parse_let(std::istream &in);
static void consumeWord(std::istream &in, std::string word);
PTR(Expr) parseInput();
std::string peek_keyword(std::istream &in);
PTR(Expr) parse_fun(istream &in);
PTR(Expr) parse_inner(std::istream &in);



//#endif //EXPRESSIONCLASSES_PARSE_HPP
