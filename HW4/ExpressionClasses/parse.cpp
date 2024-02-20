#include "parse.hpp"
#include "Expr.h"

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

Expr *parse_multicand(std::istream &in) {
    skip_whitespace(in);
    int c = in.peek();
    if ((c == '-' || isdigit(c))) {
        return parse_num(in);
    } else if (c == '('){
        consume(in, '(');
        Expr *e = parse_expr(in);
        skip_whitespace(in);
        c = in.get();
        if (c != ')') {
            throw std::runtime_error("Missing close parenthesis!");
        }
        return e;
    } else if (isalpha(c)){
        return parse_var(in);
    } else if (c == '_'){
        return parse_let(in);
    } else{
        consume(in, c);
        throw std::runtime_error("Invalid Input!");
    }
}

Expr *parse_expr(std::istream &in) {
    Expr *e;
    e = parse_addend(in);
    skip_whitespace(in);
    int c = in.peek();
    if (c == '+') {
        consume(in, '+');
        Expr *rhs = parse_expr(in);
        return new Add(e, rhs);
    } else {
        return e;
    }
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

void consume(std::istream &in, int expect) {
    int c = in.get();
    if (c != expect) {
        throw std::runtime_error("Consume mismatch!");
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
    return parse_expr(ss);
}

Expr *parse_let(std::istream &in){
    skip_whitespace(in);
    std::string _let = "_let";
    consumeWord(in, _let);

    skip_whitespace(in);
    Expr *lhs = parse_var(in);

    skip_whitespace(in);
    consume(in, '=');

    skip_whitespace(in);
    Expr *rhs = parse_expr(in);

    std::string _in = "_in";
    consumeWord(in, _in);

    skip_whitespace(in);
    Expr *body = parse_expr(in);

    return new class Let(lhs->to_string(), rhs, body);
}

static void consumeWord(std::istream &in, std::string word){
    for (char letter: word){
        int c = in.peek();
        if (c == letter){
            consume(in, c);
        }
    }
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


