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
#include "pointer.h"

using namespace std;
class Val;

typedef enum {
    prec_none,      // = 0
    prec_add,       // = 1
    prec_mult       // = 2
} precedence_t;

CLASS(Expr) {
public:
    virtual bool equals(PTR(Expr) e) = 0;
    virtual PTR(Val) interp() = 0;
//    virtual bool has_variable()= 0;
    virtual PTR(Expr) subst(string varName, PTR(Expr) replacement)  = 0;
    virtual void print (ostream& os) = 0;
    string to_string();
    void pretty_print(ostream &ostream);
    virtual void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos);
    string to_pretty_string();
};

class Num : public Expr{
public:
    int val;
    explicit Num(int val);
    bool equals(PTR(Expr) e);
    //Return the value
    virtual PTR(Val) interp();
    //Num will never have a variable.
//    bool has_variable();
    PTR(Expr) subst(string varName, PTR(Expr) replacement);
    virtual void print(ostream& os);
//    string to_string();
};

class Var : public Expr{
public:
    string name;
    Var(string name);
    virtual bool equals(PTR(Expr) e);
    virtual PTR(Val) interp();
    //Will have a variable.
//    virtual bool has_variable();
    virtual PTR(Expr) subst(string varName, PTR(Expr) replacement);
    virtual void print (ostream& os);
};

class Add :  public Expr{
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;

    Add(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    //Sum of the subexpression values
    PTR(Val) interp();
    //Check if either have a variable
//    bool has_variable();
    PTR(Expr) subst( string varName, PTR(Expr) replacement);
    virtual void print (ostream &os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos);
};

class Mult : public Expr{
public:
    PTR(Expr) lhs;
    PTR(Expr) rhs;
    Mult(PTR(Expr) lhs, PTR(Expr) rhs);
    bool equals(PTR(Expr) e);
    //The product of the subexpression values
    PTR(Val) interp();
    //Check if either have a variable
//    bool has_variable();
    PTR(Expr) subst(string varName, PTR(Expr) replacement);
    virtual void print (ostream &os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos);
};

class Let : public Expr {
public:
    string lhs; //String
    PTR(Expr) rhs; //Bound expression
    PTR(Expr) bodyExpr;
    Let(string lhs, PTR(Expr) rhs, PTR(Expr) bodyExpr);
    virtual bool equals(PTR(Expr) e);
    //The product of the subexpression values
    virtual PTR(Val) interp();
    //Check if either have a variable
//    virtual bool has_variable();
    virtual PTR(Expr) subst(string varName, PTR(Expr) replacement);
    virtual void print (ostream& os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos);
};

class BoolExpr : public Expr {
public:
    bool val;
    BoolExpr(bool b);
    virtual bool equals (PTR(Expr) e);
    virtual PTR(Val) interp();
//    virtual bool has_variable();
    virtual PTR(Expr) subst(string varName, PTR(Expr) replacement);
    virtual void print (ostream& os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos);
};

class IfExpr : public Expr {
public:
    PTR(Expr) if_;
    PTR(Expr) then_;
    PTR(Expr) else_;
    IfExpr(PTR(Expr) if_, PTR(Expr) then_, PTR(Expr) else_);

    virtual bool equals (PTR(Expr) e);
    virtual PTR(Val) interp();
//    virtual bool has_variable();
    virtual PTR(Expr) subst(string varName, PTR(Expr) replacement);
    virtual void print (ostream& os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos);
};

class EqExpr : public Expr {
public:
    PTR(Expr) rhs;
    PTR(Expr) lhs;
    EqExpr(PTR(Expr) rhs, PTR(Expr) lhs);
    virtual bool equals (PTR(Expr) e);
    virtual PTR(Val) interp();
//    virtual bool has_variable();
    virtual PTR(Expr) subst(string varName, PTR(Expr) replacement);
    virtual void print (ostream& os);
    void pretty_print_at(ostream &os, precedence_t node, bool let_parent, streampos &strmpos);
};

class FunExpr : public Expr{
public:
   string formalarg;
    PTR(Expr) body;
    FunExpr(string formalArg, PTR(Expr) body);
    virtual bool equals(PTR(Expr) e);
    virtual PTR(Val) interp();
    virtual PTR(Expr) subst(string str, PTR(Expr) e);
    virtual void print(ostream& o);
};



class CallExpr : public Expr {
public:
    PTR(Expr) toBeCalled;
    PTR(Expr) actualArg;
    CallExpr(PTR(Expr) toBeCalled, PTR(Expr) actualArg);
    bool equals(PTR(Expr) other);
    PTR(Val) interp();
    PTR(Expr) subst(const std::string var, PTR(Expr) replacement);
    void print(std::ostream& o);
};
#endif //EXPRESSIONCLASSES_EXPR_H

