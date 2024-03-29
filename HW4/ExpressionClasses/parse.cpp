#include "parse.hpp"
#include "Expr.h"
#include "pointer.h"
using namespace std;

static void consume_word(istream &in, string str){
    for(char c : str){
        if (in.get()!=c){
            throw runtime_error("consume mismatch");
        }
    }
}

PTR(Expr) parse_if( std::istream &stream ){
    skip_whitespace(stream);

    PTR(Expr) ifStatement = parse_expr(stream);

    skip_whitespace(stream);

    consume_word(stream, "_then");

    skip_whitespace(stream);

    PTR(Expr) thenStatement = parse_expr(stream);

    skip_whitespace(stream);

    consume_word(stream, "_else");

    skip_whitespace(stream);

    PTR(Expr) elseStatement = parse_expr(stream);

    return NEW(IfExpr)(ifStatement, thenStatement, elseStatement);
}

PTR(Expr) parse_expr(std::istream &in) {
    PTR(Expr) e = parse_comparg(in);
    skip_whitespace(in);
    if (in.peek() == '='){
        consume(in, '=');
        if (in.peek() != '='){
            throw runtime_error("need '=='!");
        }
        consume(in, '=');
        PTR(Expr) rhs = parse_expr(in);
        return NEW (EqExpr)(e, rhs);
    }
    return e;
}

PTR(Expr) parse_comparg(istream &in){
    PTR(Expr) e = parse_addend(in);
    skip_whitespace(in);
    if (in.peek() == '+'){
        consume(in, '+');
        PTR(Expr) rhs = parse_comparg(in);
        return NEW(Add)(e, rhs);
    }
    return e;
}

PTR(Expr) parse_addend(std::istream &in) {
    PTR(Expr) e;
    e = parse_multicand(in);
    skip_whitespace(in);

    int c = in.peek();
    if (c == '*') {
        consume(in, '*');
        skip_whitespace(in);
        PTR(Expr) rhs = parse_addend(in);
        return NEW(Mult)(e, rhs);
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
PTR(Expr) parse_multicand(istream &in) {
    PTR(Expr) e = parse_inner(in);
    while (in.peek() == '(') {
        consume(in, '(');
        PTR(Expr) actual_arg = parse_expr(in);
        consume(in, ')');
        e = NEW(CallExpr)(e, actual_arg);
    }
    return e;
}

PTR(Expr) parse_inner(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();

    if ((c == '-') || isdigit(c)){
        return parse_num(in);
    }

    else if (c == '(') {
        consume(in, '(');
        PTR(Expr) e = parse_comparg(in);
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
            return NEW(BoolExpr)(true);
        }
        else if(term == "false"){
            return NEW(BoolExpr)(false);
        }
        else if(term == "fun"){
            return parse_fun(in);
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

PTR(Expr) parse_num(std::istream &in) {

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
    return NEW(Num)(n);
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

PTR(Expr) parse(std::istream &in) {
    PTR(Expr) e;
    e = parse_expr(in);
    skip_whitespace(in);
    if (!in.eof()) {
        throw std::runtime_error("Invalid Input!");
    }
    return e;
}

PTR(Expr) parseInput() {
    std::string input;
    getline(std::cin, input);
    std::cout << "input : " << input << std::endl;
    std::stringstream ss(input);
    return parse_comparg(ss);
}


PTR(Expr) parse_let(std::istream &in){
    skip_whitespace(in);

    PTR(Expr) e = parse_var(in);

    string lhs = e->to_string();

    skip_whitespace(in);

    consume(in, '=');

    skip_whitespace(in);

    PTR(Expr) rhs = parse_comparg(in);

    skip_whitespace(in);

    consume_word(in, "_in");

    skip_whitespace(in);

    PTR(Expr) body = parse_comparg(in);

    return NEW(Let)(lhs, rhs, body);
}

PTR(Expr)parse_var(std::istream &in){
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
    return NEW(Var)(var);
}


PTR(Expr) parse_str(const string& s){
    istringstream in(s);
    return parse (in);
}

PTR(Expr) parse_fun(istream &in){
    skip_whitespace(in);

    consume(in, '(');

    PTR(Expr) e = parse_var(in);

    string var = e->to_string();

    consume(in, ')');

    skip_whitespace(in);

    e = parse_expr(in);

    return NEW(FunExpr)(var, e);

}
