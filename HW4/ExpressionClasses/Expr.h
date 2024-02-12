/**
 * \file Expr.h
 * \author Lindsay Haslam
 * \date 1/18/24
 * \brief This header file defines a hierarchy of expression classes for representing and manipulating arithmetic expressions.
 *
 * The `Expr` class hierarchy includes classes for numerical values (`Num`), variables (`Var`), addition operations (`Add`), and multiplication operations (`Mult`). Each class provides methods for equality checks, interpretation (evaluation), variable presence checks, substitution, and printing. The design supports the construction and manipulation of arithmetic expressions involving integers, variables, addition, and multiplication, allowing for pretty-printing and evaluation with variable substitution.
 */
#ifndef EXPRESSIONCLASSES_EXPR_H
#define EXPRESSIONCLASSES_EXPR_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

typedef enum {
    prec_none,      // = 0
    prec_add,       // = 1
    prec_mult       // = 2
} precedence_t;

class Expr {
public:
    virtual bool equals(Expr *e) = 0;
    virtual int interp() = 0;
    virtual bool has_variable()  = 0;
    virtual Expr* subst(string varName, Expr* replacement)  = 0;
    virtual void print (ostream& os) = 0;

    string to_string();
    void pretty_print(ostream &ostream);
    virtual void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos strmpos);
    string to_pretty_string();
};

class Num : public Expr {
public:
    int val;
    Num(int val);
    bool equals(Expr *e);
    //Return the value
    int interp();
    //Num will never have a variable.
    bool has_variable();
    Expr* subst( string varName, Expr* replacement);
    virtual void print (ostream& os);
//    string to_string();
};

class Var : public Expr{
public:
    string name;
    Var(string name);
    virtual bool equals(Expr *e);
    virtual int interp();
    //Will have a variable.
    virtual bool has_variable();
    virtual Expr* subst(string varName, Expr* replacement);
    virtual void print (ostream& os);
};

class Add : public Expr {
public:
    Expr *lhs, *rhs;
    Add(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    //Sum of the subexpression values
    int interp();
    //Check if either have a variable
    bool has_variable();
    Expr* subst( string varName, Expr* replacement);
    virtual void print (ostream& os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos strmpos);
};

class Mult : public Expr {
public:
    Expr *lhs, *rhs;
    Mult(Expr *lhs, Expr *rhs);
    bool equals(Expr *e);
    //The product of the subexpression values
    int interp();
    //Check if either have a variable
    bool has_variable();
    Expr* subst(string varName, Expr* replacement);
    virtual void print (ostream& os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos strmpos);
};

class Let : public Expr {
public:
    string lhs; //String
    Expr* rhs; //Bound expression
    Expr* bodyExpr;
    Let(string lhs, Expr* rhs, Expr* bodyExpr);
    virtual bool equals(Expr *e);
    //The product of the subexpression values
    virtual int interp();
    //Check if either have a variable
    virtual bool has_variable();
    virtual Expr* subst(string varName, Expr* replacement);
    virtual void print (ostream& os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos strmpos);
};

#endif //EXPRESSIONCLASSES_EXPR_H

