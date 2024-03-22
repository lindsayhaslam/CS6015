#include "parse.hpp"
#include "Expr.h"
using namespace std;
//
///**
// * \brief Parses an expression from a string.
// * \param s The string to parse.
// * \return A pointer to the parsed expression.
// *
// * Wraps the parse function to allow parsing from a string by converting it
// * to an std::istringstream and passing it to the parse function.
// */
//Expr* parse_str(string s){
//    istringstream in(s);
//    return parse(in);
//}
//
///**
// * \brief Parses an expression from an input stream.
// * \param in The input stream to parse.
// * \return A pointer to the parsed expression.
// * \throws std::runtime_error If the input contains invalid expressions or is not fully consumed.
// *
// * This function delegates to specific parsing functions based on the input's initial characters.
// * It ensures that the entire input stream is consumed and valid as per the parsing rules.
// */
//Expr *parse(std::istream &in) {
//    Expr* e;
//    //parse expression and skip whitespace
//    e = parse_expr(in);
//    skip_whitespace(in);
//
//    //if it's not the end of the file then throw an errpr
//    if ( !in.eof() ) {
//        throw std::runtime_error("Invalid input") ;
//    }
//    return e;
//}
//
///**
// * \brief Parses an expression including equality checks from an input stream.
// *
// * Reads an input stream to construct expressions. Handles equality by checking for
// * '==' and constructs an EqExpr with left and right expressions if found.
// *
// * \param in The input stream to parse.
// * \return A pointer to the parsed expression, possibly including equality checks.
// * \throws std::runtime_error if an equality check is malformed (missing second '=').
// */
//Expr *parse_expr(std::istream &in) {
//    Expr* e = parse_comparg(in);
//    skip_whitespace(in);
//    if(in.peek() == '='){
//        consume(in, '=');
//        if(in.peek() != '='){
//            throw std::runtime_error("need '==' to indicate equal check") ;
//        }
//        consume(in, '=');
//        Expr* rhs = parse_expr(in);
//        return new EqExpr(e, rhs);
//    }
//    return e;
//}
//
///**
// * \brief Parses an additive expression from an input stream.
// * \param in The input stream to parse.
// * \return A pointer to the parsed expression, which may be a Num, Var, Add, or other expression type.
// *
// * Attempts to parse an expression that may include addition. If a '+' is encountered,
// * it parses both sides of the addition and returns an Add expression.
// */
////from lecture 10 slides
//Expr* parse_comparg(istream &in) {
//
//    Expr *e = parse_addend(in);
//
//    skip_whitespace(in);
//
//    if (in.peek() == '+') {
//        consume(in, '+');
//        Expr *rhs = parse_comparg(in);
//        return new Add(e, rhs);
//    }
//    return e;
//}
//
///**
// * \brief Parses a multiplicative expression from an input stream.
// * \param in The input stream to parse.
// * \return A pointer to the parsed expression, potentially a Mult expression.
// *
// * Similar to parse_expr, but for multiplication. If a '*' is encountered, it parses both operands
// * and returns a Mult expression.
// */
////from lecture 10 slides (mostly)
//Expr *parse_addend(std::istream &in) {
//    Expr *e;
//    e = parse_multicand(in);
//    skip_whitespace(in);
//    int c = in.peek();
//    if (c == '*') {
//        consume(in, '*');
//        skip_whitespace(in) ;
//        Expr *rhs = parse_addend(in);
//        return new MultExpr(e, rhs);
//    }
//    else{
//        return e ;
//    }
//}
//
///**
// * \brief Parses a term from an input stream.
// * \param in The input stream to parse.
// * \return A string representing the parsed term.
// *
// * Iterates over the input, appending each alphabetical character to a term string
// * until a non-letter is encountered. Primarily used for parsing keywords or identifiers.
// */
//static string parse_term(istream &in){
//    string term;
//    while (true) {
//        int letter = in.peek();
//        if (isalpha(letter)) {
//            consume(in, letter);
//            char c = letter;
//            term += c;
//        }
//        else
//            break;
//    }
//    return term;
//}
//
///**
// * \brief Parses a multiplicand from an input stream.
// * \param in The input stream to parse.
// * \return A pointer to the parsed expression.
// * \throws std::runtime_error If the input is invalid for a multiplicand.
// *
// * A multiplicand can be a number, variable, let-expression, or a parenthesized expression.
// * Delegates to the appropriate parsing function based on the next character.
// */
//Expr* parse_multicand(istream &in) {
//    Expr* e = parse_inner(in);
//    while (in.peek() == '(') {
//        consume(in, '(');
//        Expr* actual_arg = parse_expr(in);
//        consume(in, ')');
//        e = new CallExpr(e, actual_arg);
//    }
//    return e;
//}
//
///**
// * \brief Parses the innermost expressions from an input stream.
// * \param in The input stream to parse.
// * \return A pointer to the parsed expression.
// * \throws std::runtime_error If the input is invalid or does not conform to the expected syntax.
// *
// * Manages parsing of numerics, variables, precedence parentheses, and keywords ('let', 'if', 'true', 'false', 'fun').
// * Delegates parsing based on input's first character for efficient, recursive parsing of expressions.
// */
//
//Expr* parse_inner(istream &in) {
//    skip_whitespace(in);
//    int c = in.peek();
//
//    if ((c == '-') || isdigit(c)){
//        return parse_num(in);
//    }
//
//    else if (c == '(') {
//        consume(in, '(');
//        Expr *e = parse_comparg(in);
//        skip_whitespace(in);
//        c = in.get();
//        if (c != ')'){
//            throw runtime_error("Missing close parentheses");
//        }
//        return e;
//    }
//
//    else if (isalpha(c)) {
//        return parse_var(in);
//    }
//
//    else if (c=='_'){
//        consume(in, '_');
//
//        string term = parse_term(in);
//
//        if(term == "let"){
//            return parse_let(in);
//        }
//        else if(term == "if"){
//            return parse_if(in);
//        }
//        else if(term == "true"){
//            return new BoolExpr(true);
//        }
//        else if(term == "false"){
//            return new BoolExpr(false);
//        }
//        else if(term == "fun"){
//            return parse_fun(in);
//        }
//        else{
//            throw runtime_error("Invalid input");
//        }
//    }
//    else {
//        consume(in, c);
//        throw runtime_error("Invalid input");
//    }
//}
//
//
///**
// * \brief Parses a numeric expression from an input stream.
// * \param in The input stream to parse.
// * \return A pointer to the Num expression representing the parsed number.
// * \throws std::runtime_error If the input does not start with a digit after an optional leading '-'.
// *
// * Handles both positive and negative integers. It checks for a leading '-'
// * to determine negativity and constructs a Num expression based on the parsed number.
// */
////from lecture 10 slides
//Expr *parse_num(std::istream &in) {
//    //initialize the return int as 0
//    int n = 0;
//    bool negative = false;
//    //check if the first value is a -, if it is then flip the boolean to true and consume it
//    if (in.peek() == '-') {
//        negative = true;
//        consume (in, '-');
//        //if the next input is not a digit then throw an error
//        if(!isdigit(in.peek())){
//            throw std::runtime_error("Invalid input") ;
//        }
//    }
//    //forever loop
//    while (1) {
//        //check the next input
//        int c = in.peek();
//        if (isdigit(c))
//        {
//            //consume it and set the return int to the number
//            consume(in, c);
//            n = n*10 + (c - '0');
//        }
//        else
//            break;
//    }
//    //if it's negative then make it negative
//    if (negative)
//        n = n * -1;
//    return new NumExpr(n);
//}
//
///**
// * \brief Parses a variable from an input stream.
// * \param in The input stream to parse.
// * \return A pointer to a Var expression representing the parsed variable.
// *
// * Constructs a variable name by consuming consecutive alphabetical characters.
// */
//Expr *parse_variable(std::istream &in) {
//    std::string var;
//    //forever loop
//    while (true) {
//        int c = in.peek();
//        //check that the char is valid
//        if (isalpha(c)) {
//            consume(in, c);
//            //add the char it's on to the var string
//            var += static_cast<char>(c);
//        }
//        else {
//            break;
//        }
//    }
//    //return the var
//    return new VarExpr(var);
//}
//
///**
// * \brief Consumes the next character in the input stream if it matches the expected character.
// * \param in The input stream.
// * \param expected The character expected to be next in the stream.
// * \throws std::runtime_error If the next character in the stream does not match the expected character.
// *
// * A utility used to consume specific characters, such as operators or parentheses,
// * as part of the parsing process.
// */
//void consume(std::istream &in, int expected) {
//    //get (not peek) the next input which clears it from the stream
//    int c = in.get();
//    //if it's not what's expected then throw an exception
//    if (c!=expected) {
//        throw std::runtime_error("consume CHAR mismatch");
//    }
//}
//
////same idea as above but for a whole word
//void consume(std::istream & in, const std::string & str){
//    for ( char c : str ){
//        const int real = in.get();
//        if ( real != c ){
//            throw std::runtime_error( "consume STRING mismatch" );
//        }
//    }
//}
//
//
///**
// * \brief Consumes whitespace characters from the input stream.
// * \param in The input stream from which whitespace will be consumed.
// *
// * This function iterates over the input stream and consumes all leading whitespace characters
// * until a non-whitespace character is encountered.
// */
////from lecture 10 slides
//void skip_whitespace(std::istream &in) {
//    //forever loop
//    while (true) {
//        //check what the next value in the instream is
//        int c = in.peek();
//        //if it's not a space then break out of this method
//        if (!isspace(c))
//            break;
//        //if it is a space then consume
//        consume(in, c);
//    }
//}
//
///**
// * \brief Parses a let-expression from an input stream.
// * \param in The input stream to parse.
// * \return A pointer to a Let expression constructed from the parsed components.
// * \throws std::runtime_error If the input does not conform to the expected let-expression syntax.
// *
// * A let-expression binds a variable name to an expression and then uses that binding
// * within another expression. Parses the "_let" keyword, variable name,
// * binding expression, "_in" keyword, and body expression.
// */
//Expr* parse_let(std::istream &in) {
//    skip_whitespace(in);
//
//    Expr *e = parse_variable(in);
//
//    string lhs = e->to_string();
//
//    skip_whitespace(in);
//
//    consume(in, '=');
//
//    skip_whitespace(in);
//
//    Expr *rhs = parse_comparg(in);
//
//    skip_whitespace(in);
//
//    consume(in, "_in");
//
//    skip_whitespace(in);
//
//    Expr *body = parse_comparg(in);
//
//    return new LetExpr(lhs, rhs, body);
//}
//
///**
// * \brief Parses an "if" expression from the input stream.
// * \param in The input stream to parse.
// * \return A pointer to an IfExpr constructed from the parsed components.
// *
// * Parses an "if" statement including its condition, "then" branch, and "else" branch.
// * Each part is extracted using parse_expr, with mandatory "_then" and "_else" keywords
// * indicating the start of the respective branches. Useful for interpreting conditional logic.
// */
//Expr* parse_if(istream &in){
//    skip_whitespace(in);
//
//    Expr* ifStatement = parse_expr(in);
//
//    skip_whitespace(in);
//
//    consume(in, "_then");
//
//    skip_whitespace(in);
//
//    Expr* thenStatement = parse_expr(in);
//
//    skip_whitespace(in);
//
//    consume(in, "_else");
//
//    skip_whitespace(in);
//
//    Expr* elseStatment = parse_expr(in);
//
//    return new IfExpr(ifStatement, thenStatement, elseStatment);
//}
//
///**
// * \brief Parses a function expression from an input stream.
// * \param in The input stream to parse from.
// * \return A pointer to a constructed FunExpr.
// * \throws std::runtime_error For syntax errors.
// *
// * Parses function expressions defined by a 'fun' keyword. It expects a variable name
// * enclosed in parentheses followed by an expression. The function constructs a FunExpr
// * with the parsed variable as the argument and the subsequent expression as the function body.
// */
//Expr* parse_fun(istream &in){
//    skip_whitespace(in);
//
//    consume(in, '(');
//
//    Expr* e = parse_variable(in);
//
//    string var = e->to_string();
//
//    consume(in, ')');
//
//    skip_whitespace(in);
//
//    e = parse_expr(in);
//
//    return new FunExpr(var, e);
//
//}

//LINDSAY

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

Expr* parse_multicand(istream &in) {
    Expr* e = parse_inner(in);
    while (in.peek() == '(') {
        consume(in, '(');
        Expr* actual_arg = parse_expr(in);
        consume(in, ')');
        e = new CallExpr(e, actual_arg);
    }
    return e;
}

Expr *parse_inner(std::istream &in) {
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


Expr *parse_str(const string& s){
    istringstream in(s);
    return parse (in);
}

Expr* parse_fun(istream &in){
    skip_whitespace(in);

    consume(in, '(');

    Expr* e = parse_var(in);

    string var = e->to_string();

    consume(in, ')');

    skip_whitespace(in);

    e = parse_expr(in);

    return new FunExpr(var, e);

}

//Peek keyword function, res = "IF" type stuff. Make sure you have a putback _.
//Parse keyword is in the slides.
