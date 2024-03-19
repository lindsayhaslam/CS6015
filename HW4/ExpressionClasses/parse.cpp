#include "parse.hpp"
#include "Expr.h"


static void consume_word(istream &in, string str){
    for(char c : str){
        if (in.get()!=c){
            throw runtime_error("consume mismatch");
        }
    }
}

Expr* parse_if( std::istream &stream ){
    skip_whitespace(stream);

    Expr* ifStatement = parse_expr(stream);

    skip_whitespace(stream);

    consume_word(stream, "_then");

    skip_whitespace(stream);

    Expr* thenStatement = parse_expr(stream);

    skip_whitespace(stream);

    consume_word(stream, "_else");

    skip_whitespace(stream);

    Expr* elseStatement = parse_expr(stream);

    return new IfExpr(ifStatement, thenStatement, elseStatement);
//    consume( stream, "_if" );
//    Expr * test = parse_expr( stream );
//
//    consume( stream, "_then" );
//    Expr * then = parse_expr( stream );
//
//    consume( stream, "_else" );
//    Expr * el = parse_expr( stream );
//
//    return new IfExpr( test, then, el );
}

Expr *parse_expr(std::istream &in) {
    Expr* e = parse_comparg(in);
    skip_whitespace(in);
    if (in.peek() == '='){
        consume(in, '=');
        if (in.peek() != '='){
            throw runtime_error("need '=='!");
        }
        consume(in, '=');
        Expr* rhs = parse_expr(in);
        return new EqExpr(e, rhs);
    }
    return e;
}

Expr* parse_comparg(istream &in){
    Expr *e = parse_addend(in);
    skip_whitespace(in);
    if (in.peek() == '+'){
        consume(in, '+');
        Expr *rhs = parse_comparg(in);
        return new Add(e, rhs);
    }
    return e;
}

Expr *parse_addend(std::istream &in) {
    Expr *e;
    e = parse_multicand(in);
    skip_whitespace(in);

    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        skip_whitespace(in);
        Expr *rhs = parse_addend(in);
        return new Mult(e, rhs);
    } else {
        return e;
    }
}

static string parse_term(istream &in){
    string term;
    while (true) {
        int letter = in.peek();
        if (isalpha(letter)) {
            consume(in, letter);
            char c = letter;
            term += c;
        }
        else
            break;
    }
    return term;
}

Expr *parse_multicand(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();

    if ((c == '-') || isdigit(c)){
        return parse_num(in);
    }

    else if (c == '(') {
        consume(in, '(');
        Expr *e = parse_comparg(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')'){
            throw runtime_error("Missing close parenthesis!");
        }
        return e;
    }

    else if (isalpha(c)) {
        return parse_var(in);
    }

    else if (c=='_'){
        consume(in, '_');

        string term = parse_term(in);

        if(term == "let"){
            return parse_let(in);
        }
        else if(term == "if"){
            return parse_if(in);
        }
        else if(term == "true"){
            return new BoolExpr(true);
        }
        else if(term == "false"){
            return new BoolExpr(false);
        }
        else{
            throw runtime_error("Invalid Input!");
        }
    }
    else {
        consume(in, c);
        throw runtime_error("Invalid Input!");
    }
}

Expr *parse_num(std::istream &in) {

    int n = 0;
    bool negative = false;
    bool digitSeen = false;

    if (in.peek() == '-') {
        negative = true;
        consume(in, '-');
    }

    while (1) {
        int c = in.peek();
        if (isdigit(c)) {
            consume(in, c);
            n = n * 10 + (c - '0');
            digitSeen = true;
        } else
            break;
    }
    if (negative && !digitSeen){
        throw std::runtime_error("Invalid Input!");
    }
    if (negative) {
        n = -n;
    }
    return new Num(n);
}


void consume(std::istream &in, int expect) {
    int c = in.get();
    if (c != expect) {
        throw std::runtime_error("Consume mismatch!");
    }
}

//Polymorphic consume
void consume( std::istream & stream, const std::string & str)
{
    for ( char expect : str )
    {
        const int c = stream.get();
        if ( c != expect )
            throw std::runtime_error( "consume(): mismatch" );
    }
}

void skip_whitespace(std::istream &in) {
    while (1) {
        int c = in.peek();
        if (!isspace(c))
            break;
        consume(in, c);
    }
}

Expr *parse(std::istream &in) {
    Expr *e;
    e = parse_expr(in);
    skip_whitespace(in);
    if (!in.eof()) {
        throw std::runtime_error("Invalid Input!");
    }
    return e;
}

Expr *parseInput() {
    std::string input;
    getline(std::cin, input);
    std::cout << "input : " << input << std::endl;
    std::stringstream ss(input);
    return parse_comparg(ss);
}


Expr *parse_let(std::istream &in){
    skip_whitespace(in);

    Expr *e = parse_var(in);

    string lhs = e->to_string();

    skip_whitespace(in);

    consume(in, '=');

    skip_whitespace(in);

    Expr *rhs = parse_comparg(in);

    skip_whitespace(in);

    consume_word(in, "_in");

    skip_whitespace(in);

    Expr *body = parse_comparg(in);

    return new Let(lhs, rhs, body);
}

Expr *parse_var(std::istream &in){
    std::string var;
    while(true){
        int c = in.peek();
        if (isalpha(c)){
            consume(in, c);
            var += static_cast<char>(c);
        } else {
            break;
        }
    }
    return new Var(var);
}


Expr *parse_str(string s){
    istringstream in(s);
    return parse (in);
}

//Peek keyword function, res = "IF" type stuff. Make sure you have a putback _.
//Parse keyword is in the slides.
